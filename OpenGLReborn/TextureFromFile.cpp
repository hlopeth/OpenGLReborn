#include "TextureFromFile.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;
	
	int width, height, nrComponents;
	FILE *fp;
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp) {
		std::cout << "[read_png_file] File %s could not be opened for reading" << filename << std::endl;
		return 0;
	}
	char header[8];

	fread(header, 1, 8, fp);
	if (png_sig_cmp((png_const_bytep)header, 0, 8)) {
		std::cout << "[read_png_file] File %s is not recognized as a PNG file" << filename << std::endl;
		return 0;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		std::cout << "[read_png_file] png_create_read_struct failed" << std::endl;
		return 0;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		std::cout << "[read_png_file] png_create_info_struct failed" << std::endl;
		return 0;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout << "[read_png_file] Error during init_io" << std::endl;
		return 0;
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
		std::cout << "[read_png_file] Error during read_image" << std::endl;
	}



	png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++)
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

	png_read_image(png_ptr, row_pointers);

	fclose(fp);

	unsigned char *data;
	//unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if(row_pointers)//if (data)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);

		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, row_pointers);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return textureID;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		return 0;
	}
}