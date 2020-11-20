#include "TextureRenderTarget.h"
#include "AbstractRenderer.h"

TextureRenderTarget::TextureRenderTarget()
{
	fbo = -1;
	rbo = -1;
	texture = nullTexture;
}

TextureRenderTarget::TextureRenderTarget(size_t width, size_t height)
{
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);
	bind();
	texture.init(
		nullptr,
		GL_RGB,
		GL_CLAMP_TO_EDGE,
		GL_CLAMP_TO_EDGE,
		GL_LINEAR,
		GL_LINEAR,
		false,
		false
	);
	AbstractRenderer::checkGLErrors();
	allocate(width, height);
	AbstractRenderer::checkGLErrors();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

TextureRenderTarget::~TextureRenderTarget()
{
	glDeleteFramebuffers(1, &fbo);
}

void TextureRenderTarget::allocate(size_t width, size_t height)
{
	bind();
	AbstractRenderer::checkGLErrors();
	texture.allocate(width, height);
	AbstractRenderer::checkGLErrors();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);
	AbstractRenderer::checkGLErrors();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	AbstractRenderer::checkGLErrors();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	AbstractRenderer::checkGLErrors();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void TextureRenderTarget::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
}

bool TextureRenderTarget::isComplete() const
{
	bind();
	auto st = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

GLuint TextureRenderTarget::getFbo() const
{
	return fbo;
}

GLuint TextureRenderTarget::getRbo() const
{
	return rbo;
}

GLTexture TextureRenderTarget::getTexture() const
{
	return texture;
}
