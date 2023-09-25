#include "ModuleEditor.h"
#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

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



    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

	return ret;
}

void ModuleEditor::DrawEditor()
{

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Here goes the code for the editor

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

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

bool ModuleEditor::CleanUp()
{
    bool ret = true;

    // Cleanup
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
