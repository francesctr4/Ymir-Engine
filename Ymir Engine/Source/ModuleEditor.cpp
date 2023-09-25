#include "ModuleEditor.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

//#include "External/Parson/parson.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app,start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
    bool ret = true;

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

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

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

    // Here starts the code for the editor

    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {

            ImGui::Text("Hello, world!");
            ImGui::EndMenu();

        }
        ImGui::EndMainMenuBar();
    }

    /*if (ImGui::Begin("Configuration")) {

        ImGui::PlotHistogram("FPS", &mFPSLog[0], mFPSLog.size());
        ImGui::End();

    }*/

    ImGui::ShowDemoWindow();

    // Here finishes the code for the editor
    
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

    /*if (mFPSLog.size() < 30) {

        mFPSLog.push_back(aFPS);

    }
    else {

        std::vector<float> mTempFPS;
        mTempFPS.reserve(30);
        memcpy(&mTempFPS[0], &mFPSLog[1], 29);
        mTempFPS.push_back(aFPS);
        mFPSLog = mTempFPS;
    }*/

}
