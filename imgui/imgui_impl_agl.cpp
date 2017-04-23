// ImGui with AllegroGL
// Mainly based on ImGui with freeglut by azer89 (https://github.com/azer89/imgui_freeglut) and modifications by bitxue (https://github.com/ocornut/imgui/pull/801)

// You can copy and use unmodified imgui_impl_* files in your project.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// See main.cpp for an example of using this.
// https://github.com/ocornut/imgui


#include "imgui.h"
#include "imgui_impl_agl.h"

#include <allegro.h>
#ifdef ALLEGRO_WINDOWS
#include <winalleg.h>
#endif
#include <GL/gl.h>
#include <alleggl.h>
#include <bitset>

// Data
static double       ImGui_ImplAGL_Time = 0.0f;
static GLuint       ImGui_ImplAGL_FontTexture = 0;

void ImGui_ImplAGL_LowLevelKeyboardHandler(int scancode)
{
	ImGuiIO& io = ImGui::GetIO();
	if(scancode & 0x80) {
		io.KeysDown[scancode & ~0x80] = false;
		//std::cout << "UP";
	}
} END_OF_FUNCTION(ImGui_ImplAGL_LowLevelKeyboardHandler)

int ImGui_ImplAGL_KeyboardHandler(int key, int* scancode)
{
	ImGuiIO& io = ImGui::GetIO();
	//std::cout << std::bitset<16>(key) <<" "<< std::bitset<16>(key|0x60)<< " " << (char) key <<" " << std::bitset<16>(*scancode) << " isascii: " << (key>32 && key != 127 )<< " ctrl: " << ( key_shifts & KB_CTRL_FLAG ) << " " << ( *scancode == KEY_SPACE )<< std::endl;
	io.KeyCtrl = (key_shifts & KB_CTRL_FLAG) != 0;
	io.KeyShift = (key_shifts & KB_SHIFT_FLAG) != 0;
	io.KeyAlt = (key_shifts & KB_ALT_FLAG) != 0;
	io.KeySuper = ((key_shifts & KB_LWIN_FLAG) != 0) || ((key_shifts & KB_RWIN_FLAG) != 0);

	if(key>32 && key != 127)
	{
		io.AddInputCharacter(key);
	}
	else
	{
		if(io.KeyCtrl)
			io.AddInputCharacter(key|0x60);
		else if(key == ' ')
			io.AddInputCharacter(' ');
		else
			io.KeysDown[*scancode] = true;
	}
	return key;
} END_OF_FUNCTION(ImGui_ImplAGL_KeyboardHandler)

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// If text or lines are blurry when integrating ImGui in your engine:
// - in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
void ImGui_ImplAGL_RenderDrawLists(ImDrawData* draw_data)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // We are using the OpenGL fixed pipeline to make the example code simpler to read!
    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, vertex/texcoord/color pointers.
    GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_TEXTURE_2D);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context

    // Setup viewport, orthographic projection matrix
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Render command lists
    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
        const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
            }
            idx_buffer += pcmd->ElemCount;
        }
    }
    #undef OFFSETOF

    // Restore modified state
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
}

bool ImGui_ImplAGL_CreateDeviceObjects()
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

	// Upload texture to graphics system
	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	glGenTextures(1, &ImGui_ImplAGL_FontTexture);
	glBindTexture(GL_TEXTURE_2D, ImGui_ImplAGL_FontTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

	// Store our identifier
	io.Fonts->TexID = (void *)(intptr_t)ImGui_ImplAGL_FontTexture;

	// Restore state
	glBindTexture(GL_TEXTURE_2D, last_texture);

	return true;
}

void ImGui_ImplAGL_InvalidateDeviceObjects()
{
	if (ImGui_ImplAGL_FontTexture)
	{
		glDeleteTextures(1, &ImGui_ImplAGL_FontTexture);
		ImGui::GetIO().Fonts->TexID = 0;
		ImGui_ImplAGL_FontTexture = 0;
	}
}

bool ImGui_ImplAGL_Init()
{
	ImGuiIO& io = ImGui::GetIO();

	io.RenderDrawListsFn = ImGui_ImplAGL_RenderDrawLists;   // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.

	io.KeyMap[ImGuiKey_Tab]        = KEY_TAB;        // tab
	io.KeyMap[ImGuiKey_LeftArrow]  = KEY_LEFT;      // Left
	io.KeyMap[ImGuiKey_RightArrow] = KEY_RIGHT;     // Right
	io.KeyMap[ImGuiKey_UpArrow]    = KEY_UP;        // Up
	io.KeyMap[ImGuiKey_DownArrow]  = KEY_DOWN;      // Down
	io.KeyMap[ImGuiKey_Home]       = KEY_HOME;      // Home
	io.KeyMap[ImGuiKey_End]        = KEY_END;       // End
	io.KeyMap[ImGuiKey_Delete]     = KEY_DEL;       // Delete
	io.KeyMap[ImGuiKey_Backspace]  = KEY_BACKSPACE; // Backspace
	io.KeyMap[ImGuiKey_Enter]      = KEY_ENTER;     // Enter
	io.KeyMap[ImGuiKey_Escape]     = KEY_ESC;       // Escape
	io.KeyMap[ImGuiKey_A]          = 'a';           // A
	io.KeyMap[ImGuiKey_C]          = 'c';           // C
	io.KeyMap[ImGuiKey_V]          = 'v';           // V
	io.KeyMap[ImGuiKey_X]          = 'x';           // X
	io.KeyMap[ImGuiKey_Y]          = 'y';           // Y
	io.KeyMap[ImGuiKey_Z]          = 'z';           // Z

	LOCK_FUNCTION(ImGui_ImplAGL_KeyboardHandler);
	LOCK_FUNCTION(ImGui_ImplAGL_LowLevelKeyboardHandler);

	keyboard_ucallback = ImGui_ImplAGL_KeyboardHandler;
	keyboard_lowlevel_callback = ImGui_ImplAGL_LowLevelKeyboardHandler;

	return true;
}

void ImGui_ImplAGL_Shutdown()
{
	ImGui_ImplAGL_InvalidateDeviceObjects();
	ImGui::Shutdown();
}

void ImGui_ImplAGL_NewFrame(float dTime)
{
	if (!ImGui_ImplAGL_FontTexture)
		ImGui_ImplAGL_CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	io.DisplaySize = ImVec2((float)SCREEN_W, (float)SCREEN_H);

	// Setup mouse cursor position and mouse buttons status every frame
	io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
	io.MouseDown[0] = (mouse_b & 0b001) != 0;
	io.MouseDown[1] = (mouse_b & 0b010) != 0;
	io.MouseDown[2] = (mouse_b & 0b100) != 0;

	// Setup time step
	io.DeltaTime = ( dTime >= 0 ? dTime : 1 / 60.f );

	// Start the frame
	ImGui::NewFrame();
}