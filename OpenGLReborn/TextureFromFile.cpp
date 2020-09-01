#include "TextureFromFile.h"
#include "TextureReadExeption.h"
#include <string>
#include <iostream>
#include <libpng/png.h>
#include <glad/glad.h>

using std::string;

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;
	
	int width, height;
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp) {
		throw TextureReadExeption(filename, "[read_png_file] File %s could not be opened for reading");
	}
	char header[8];

	fread(header, 1, 8, fp);
	if (png_sig_cmp((png_const_bytep)header, 0, 8)) {
		throw TextureReadExeption(filename, "[read_png_file] File %s is not recognized as a PNG file");
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		throw TextureReadExeption(filename, "[read_png_file] png_create_read_struct failed");
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		throw TextureReadExeption(filename, "[read_png_file] png_create_info_struct failed");
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		throw TextureReadExeption(filename, "[read_png_file] Error during init_io");
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	int number_of_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);


	/* read file */
	if (setjmp(png_jmpbuf(png_ptr))) {
		throw TextureReadExeption(filename, "[read_png_file] Error during read_image");
	}


	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	
	// Allocate the image_data as a big block, to be given to opengl
	png_byte * image_data = (png_byte*)malloc(rowbytes * height);
	if (image_data == NULL)
	{
		fclose(fp);
		throw TextureReadExeption(filename, "error: could not allocate memory for PNG image data");
	}

	// row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = (png_bytep *)malloc(height * sizeof(png_bytep));
	if (row_pointers == NULL)
	{
		free(image_data);
		fclose(fp);
		throw TextureReadExeption(filename, "error: could not allocate memory for PNG row pointers");
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (int i = 0; i < height; i++)
	{
		//row_pointers[height - 1 - i] = image_data + i * rowbytes;
		row_pointers[i] = image_data + i * rowbytes;
	}

	// read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);
	   
	fclose(fp);

	if(image_data)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		GLenum format = GL_RGB;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return textureID;
	}
	else
	{
		throw TextureReadExeption(filename, "Texture failed to load");
	}
}
