#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	FBO = 0; // Frame Buffer Object
	TCB = 0; // Texture Color Buffer
	RBO = 0; // Render Buffer Object

}

void FrameBuffer::Load()
{
	// Generate a Framebuffer Object (FBO)

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create a Texture Attachment (Texture Color Buffer [TCB])

	glGenTextures(1, &TCB);
	glBindTexture(GL_TEXTURE_2D, TCB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TCB, 0);

	// Create a Renderbuffer Attachment

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Check Framebuffer Completeness

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {

		LOG("Framebuffer is not complete");

	}

	// Bind the Default Framebuffer

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Render(bool toggle)
{
	if (toggle) {

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	else {

		glBindFramebuffer(GL_FRAMEBUFFER, 0); 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
}

void FrameBuffer::Delete()
{
	glDeleteRenderbuffers(1, &RBO);
	glDeleteTextures(1, &TCB);
	glDeleteFramebuffers(1, &FBO);
}
