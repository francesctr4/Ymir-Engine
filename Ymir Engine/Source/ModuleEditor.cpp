#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <fstream>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleInput.h"

#include "External/SDL/include/SDL_opengl.h"
#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"
//#include "External/Parson/parson.h"

// Constructor
ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app,start_enabled)
{
    // Reserve memory for Framerate Histograms vectors
    FPSvec.reserve(30);
    DTvec.reserve(30);
    MSvec.reserve(30);

    licenseFileContents = ReadFile("../../LICENSE");
}

// Destructor
ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
    bool ret = true;

    // Retrieving data from window initial status

    windowWidth = App->window->width;
    windowHeight = App->window->height;
    opacity = 1.0f;

    // Setup Dear ImGui context

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

        UpdateAndRenderAdditionalPlatformWindows = true;

    }

    // Setup Dear ImGui style

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.

    ImGuiStyle& style = ImGui::GetStyle();
    
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

    // ----------------------------------------------
    
    // JSON parser quick implementation (Parson)

    //JSON_Value* root_value = json_value_init_object();
    //JSON_Object* root_object = json_value_get_object(root_value);

    //json_object_set_string(root_object, "name", "John Doe");
    //json_object_set_number(root_object, "age", 30);
    //json_object_set_boolean(root_object, "isStudent", false);

    //FILE* file = fopen("output.json", "w");
    //if (file) {
    //    char* serialized_json = json_serialize_to_string_pretty(root_value); // Pretty-printed JSON
    //    if (serialized_json) {
    //        fprintf(file, "%s\n", serialized_json);
    //        json_free_serialized_string(serialized_json);
    //    }
    //    fclose(file);
    //}

    //json_value_free(root_value);

	return ret;
}

void ModuleEditor::DrawEditor()
{
    // Start the Dear ImGui frame

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // --------------------------------- Here starts the code for the editor ----------------------------------------

    // MAIN MENU BAR START

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            ImGui::SeparatorText("Scene");

            if (ImGui::MenuItem("New Scene")) {



            }

            if (ImGui::MenuItem("Open Scene")) {



            }

            ImGui::SeparatorText("Save");

            if (ImGui::MenuItem("Save")) {



            }

            if (ImGui::MenuItem("Save As...")) {



            }

            ImGui::SeparatorText("Project");

            if (ImGui::MenuItem("New Project")) {



            }

            if (ImGui::MenuItem("Open Project")) {



            }

            ImGui::SeparatorText("Exit");

            if (ImGui::MenuItem("Exit")) {

                App->input->quit = true;

            }

            ImGui::EndMenu();
       
        }

        if (ImGui::BeginMenu("Edit")) {




            ImGui::EndMenu();

        }

        if (ImGui::BeginMenu("View")) {



            ImGui::EndMenu();

        }

        if (ImGui::BeginMenu("GameObject")) {



            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {

            if (ImGui::MenuItem("About")) {

                showAboutPopUp = true;

            }

            if (ImGui::MenuItem("Repository")) {

                RequestBrowser("https://github.com/francesctr4/Ymir-Engine");

            }

            if (ImGui::MenuItem("Documentation")) {

                

            }

            if (ImGui::MenuItem("Releases")) {



            }

            if (ImGui::MenuItem("Bug report")) {



            }

            ImGui::EndMenu();

        }

        ImGui::EndMainMenuBar();

    }

    if (showAboutPopUp) {

        ImGui::OpenPopup("About");

        if (ImGui::BeginPopupModal("About")) {

            AboutModalWindowContent();

            ImGui::EndPopup();

        }

    }

    // END OF MAIN MENU BAR

    // APPLICATION MENU START

    if (ImGui::Begin("Application"), true) {

        if (ImGui::CollapsingHeader("Configuration")) {

            // FPS Graph

            char title[50];

            sprintf_s(title, 50, "Framerate (FPS): %.3f", FPSvec[FPSvec.size() - 1]);
            ImGui::PlotHistogram("## Framerate", &FPSvec[0], FPSvec.size(), 0, title, 0.0f, 250.0f, ImVec2(300, 100));

            sprintf_s(title, 50, "DeltaTime (DT): %.3f", DTvec[DTvec.size() - 1]);
            ImGui::PlotHistogram("## DeltaTime", &DTvec[0], DTvec.size(), 0, title, 0.0f, 0.032f, ImVec2(300, 100));

            sprintf_s(title, 50, "Milliseconds (MS): %.3f", MSvec[MSvec.size() - 1]);
            ImGui::PlotHistogram("## Milliseconds", &MSvec[0], MSvec.size(), 0, title, 0.0f, 32.0f, ImVec2(300, 100));

        }

        if (ImGui::CollapsingHeader("Window")) {

            // Window Options

            ImGui::Indent(); // Indent to make the checkbox visually nested under the header

            // Light/Dark Mode Checkbox
            if (ImGui::Checkbox("Toggle light mode", &lightMode)) {

                ToggleLightMode(lightMode);

            }

            // ImGui Demo Window Checkbox
            if (ImGui::Checkbox("Show ImGui demo window", &showImGuiDemo));

            // Width and Height Sliders
            ImGui::SliderInt("Width", &windowWidth, 0, 1280);
            ImGui::SliderInt("Height", &windowHeight, 0, 1024);
            SDL_SetWindowSize(App->window->window, windowWidth, windowHeight);

            // Opacity Slider
            ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f);
            SDL_SetWindowOpacity(App->window->window, opacity);

            // Window Options Checkbox
            if (ImGui::Checkbox("Fullscreen", &fullscreen)) {

                ToggleFullscreen(fullscreen);

            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Resizable", &resizable)) {

                ToggleResizable(resizable);

            }

            if (ImGui::Checkbox("Borderless", &borderless)) {

                ToggleBorderless(borderless);

            }
            ImGui::SameLine();
            if (ImGui::Checkbox("Fullscreen Desktop", &fullscreenDesktop)) {

                ToggleFullscreenDesktop(fullscreenDesktop);

            }

            ImGui::Unindent(); // Unindent to return to the previous level of indentation

        }

        if (ImGui::CollapsingHeader("Hardware")) {

            // Hardware Detection

            ShowPlatformInfo();

            ImGui::Separator();

            ShowCPUInfo();

            ImGui::Separator();

            ShowRAMInfo();

            ImGui::Separator();

            ShowGPUInfo();

            ImGui::Separator();

            ShowDiskInfo();

        }

        ImGui::End();
    }

    // END OF APPLICATION MENU

    if (showImGuiDemo) {

        ImGui::ShowDemoWindow();

    }

    // --------------------------------- Here finishes the code for the editor ----------------------------------------
    
    // Rendering

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
       // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
       //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)

    if (UpdateAndRenderAdditionalPlatformWindows) {

        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

    }

}

bool ModuleEditor::CleanUp()
{
    bool ret = true;

    // ImGui CleanUp

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

	return ret;
}

void ModuleEditor::AddFPS(const float aFPS)
{
    if (FPSvec.size() < 30) {

        FPSvec.push_back(aFPS);

    }
    else {

        for (int i = 0; i < FPSvec.size(); i++) {

            if (i + 1 < FPSvec.size()) {

                float copy = FPSvec[i + 1];
                FPSvec[i] = copy;

            }
            
        }
        FPSvec[FPSvec.capacity() - 1] = aFPS;
    }

}

void ModuleEditor::AddDT(const float aDT)
{
    if (DTvec.size() < 30) {

        DTvec.push_back(aDT);

    }
    else {

        for (int i = 0; i < DTvec.size(); i++) {

            if (i + 1 < DTvec.size()) {

                float copy = DTvec[i + 1];
                DTvec[i] = copy;

            }

        }
        DTvec[DTvec.capacity() - 1] = aDT;
    }

}

void ModuleEditor::AddMS(const float aMS)
{
    if (MSvec.size() < 30) {

        MSvec.push_back(aMS);

    }
    else {

        for (int i = 0; i < MSvec.size(); i++) {

            if (i + 1 < MSvec.size()) {

                float copy = MSvec[i + 1];
                MSvec[i] = copy;

            }

        }
        MSvec[MSvec.capacity() - 1] = aMS;
    }

}

void ModuleEditor::RequestBrowser(const char* url)
{
    HINSTANCE result = ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
}

void ModuleEditor::ToggleFullscreen(bool fullscreen)
{
    if (fullscreen) {

        SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);

    }
    else {

        SDL_SetWindowFullscreen(App->window->window, 0);

    }
}

void ModuleEditor::ToggleResizable(bool resizable)
{
    if (resizable) {

        SDL_SetWindowResizable(App->window->window, SDL_TRUE);

    }
    else {

        SDL_SetWindowResizable(App->window->window, SDL_FALSE);

    }
}

void ModuleEditor::ToggleBorderless(bool borderless)
{
    if (borderless) {

        SDL_SetWindowBordered(App->window->window, SDL_FALSE);

    }
    else {

        SDL_SetWindowBordered(App->window->window, SDL_TRUE);

    }
}

void ModuleEditor::ToggleFullscreenDesktop(bool fullscreenDesktop)
{
    if (fullscreenDesktop) {

        SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    }
    else {

        SDL_SetWindowFullscreen(App->window->window, 0);

    }
}

void ModuleEditor::ToggleLightMode(bool lightMode)
{
    if (lightMode) {

        ImGui::StyleColorsLight();

    }
    else {

        ImGui::StyleColorsDark();

    }
}

void ModuleEditor::ShowPlatformInfo() {

    ImGui::Text("Platform:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", SDL_GetPlatform());

    ImGui::Text("SDL Version:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "2.0.4");

}

void ModuleEditor::ShowCPUInfo()
{
    ImGui::Text("CPU Cores:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), std::to_string(SDL_GetCPUCount()).c_str());

    ImGui::Text("CPU Cache:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s kb", std::to_string(SDL_GetCPUCacheLineSize()).c_str());

    ImGui::Text("Caps:");
    ImGui::SameLine();

    if (SDL_Has3DNow()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "3DNow,");

    }

    ImGui::SameLine();

    if (SDL_HasAltiVec()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Altivec,");

    }

    ImGui::SameLine();

    if (SDL_HasAVX()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "AVX,");

    }

    ImGui::SameLine();

    if (SDL_HasAVX2()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "AVX2,");

    }

    ImGui::SameLine();

    if (SDL_HasMMX()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "MMX,");

    }

    ImGui::SameLine();

    if (SDL_HasRDTSC()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "RDTSC,");

    }

    ImGui::SameLine();

    if (SDL_HasSSE()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SSE,");

    }

    if (SDL_HasSSE2()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SSE2,");

    }

    ImGui::SameLine();

    if (SDL_HasSSE3()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SSE3,");

    }

    ImGui::SameLine();

    if (SDL_HasSSE41()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SSE41,");

    }

    ImGui::SameLine();

    if (SDL_HasSSE42()) {

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "SSE42");

    }

}

void ModuleEditor::ShowGPUInfo()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    ImGui::Text("GPU:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", renderer);

    const GLubyte* version = glGetString(GL_VERSION);
    ImGui::Text("OpenGL version supported:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", version);

    GLint totalMemoryKB = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemoryKB);
    ImGui::Text("Total VRAM:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f mb", static_cast<float>(totalMemoryKB / 1000.0f));

    GLint currentMemoryKB = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currentMemoryKB);
    ImGui::Text("Available VRAM:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f mb", static_cast<float>(currentMemoryKB / 1000.0f));

    PERFORMANCE_INFORMATION perfInfo;
    GetPerformanceInfo(&perfInfo, sizeof(perfInfo));
    ImGui::Text("VRAM Usage:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f mb", static_cast<float>(perfInfo.CommitTotal / 1000000.0f));
}

void ModuleEditor::ShowRAMInfo()
{
    ImGui::Text("System Total RAM:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.2f gb", static_cast<float>(SDL_GetSystemRAM()) / 1000.0f);

    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);

    ImGui::Text("Available RAM:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f mb", static_cast<float>(memStatus.ullAvailPhys / (1024.0f * 1024.0f)));

    ImGui::Text("Total RAM Usage:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f mb", static_cast<float>(memStatus.ullTotalPhys - memStatus.ullAvailPhys) / (1024.0f * 1024.0f));
}

void ModuleEditor::ShowDiskInfo()
{
    ULARGE_INTEGER totalFreeBytes;
    ULARGE_INTEGER totalBytes;
    ULARGE_INTEGER totalFreeBytesToCaller;

    GetDiskFreeSpaceEx(
        nullptr,                   // Use the default drive (usually C:)
        &totalFreeBytesToCaller,   // Total number of free bytes available to the caller
        &totalBytes,               // Total number of bytes on the disk
        &totalFreeBytes            // Total number of free bytes on the disk
    );

    double totalSpaceGB = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);
    double freeSpaceGB = static_cast<double>(totalFreeBytes.QuadPart) / (1024 * 1024 * 1024);

    ImGui::Text("Total C: Disk Space:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f gb", static_cast<float>(totalSpaceGB));

    ImGui::Text("Available C: Disk Space:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.3f gb", static_cast<float>(freeSpaceGB));
}

void ModuleEditor::AboutModalWindowContent()
{
    ImGui::Text("Ymir Engine v0.0");

    ImGui::NewLine();

    ImGui::Text("(Description)");

    ImGui::NewLine();

    ImGui::SeparatorText("AUTHORS");
    ImGui::NewLine();

    ImGui::Text("Francesc Teruel Rodriguez ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "francesctr4");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/francesctr4");

    }

    ImGui::Text("Joel Romero Botella ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "Joeltecke25");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/Joeltecke25");

    }

    ImGui::NewLine();
    ImGui::SeparatorText("THIRD PARTY LIBRARIES");
    ImGui::NewLine();

    ImGui::BulletText("ImGui v1.89.9 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/ocornut/imgui");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/ocornut/imgui");

    }

    ImGui::BulletText("MathGeoLib v1.5.0 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/juj/MathGeoLib");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/juj/MathGeoLib");

    }

    ImGui::BulletText("mmgr ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");

    }

    ImGui::BulletText("Glew v2.2.0 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/nigels-com/glew");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/nigels-com/glew");

    }

    ImGui::BulletText("SDL v2.0.4 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/libsdl-org/SDL");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/libsdl-org/SDL");

    }

    ImGui::BulletText("OpenGL v4.6.0 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://www.opengl.org/");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://www.opengl.org/");

    }

    ImGui::BulletText("Optick v1.4.0 ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/bombomby/optick");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/bombomby/optick");

    }

    ImGui::BulletText("Parson ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/kgabis/parson");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/kgabis/parson");

    }

    ImGui::NewLine();
    ImGui::SeparatorText("LICENSE");
    ImGui::NewLine();

    ImGui::TextWrapped("%s", licenseFileContents.c_str());

    ImGui::NewLine();
    if (ImGui::Button("Close")) {

        showAboutPopUp = false;

        ImGui::CloseCurrentPopup();

    }
}

std::string ModuleEditor::ReadFile(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {

        return "Error: Unable to open file.";

    }

    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return fileContents;
}

void ModuleEditor::RedirectLogOutput()
{
    // TODO
}