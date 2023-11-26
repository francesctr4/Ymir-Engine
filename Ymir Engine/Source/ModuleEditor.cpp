#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <fstream>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleScene.h"

#include "GameObject.h"

#include "External/SDL/include/SDL_opengl.h"

#include "External/ImGui/imgui.h"
#include "External/ImGui/backends/imgui_impl_sdl2.h"
#include "External/ImGui/backends/imgui_impl_opengl3.h"
#include "External/ImGuizmo/include/ImGuizmo.h"

#include "External/Assimp/include/version.h"

#include "External/Optick/include/optick.h"

// Constructor
ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app,start_enabled)
{
    // Reserve memory for Framerate Histograms vectors
    FPSvec.reserve(30);
    DTvec.reserve(30);
    MSvec.reserve(30);
    
    licenseFileContents = ReadFile("../../LICENSE");
    memleaksFileContents = ReadFile("memleaks.log");
    AssimpLogFileContents = ReadFile("AssimpLog.txt");

    LOG("Creating ModuleEditor");

}

// Destructor
ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
    LOG("Initializing editor...");

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

	return ret;
}

void ModuleEditor::DrawEditor()
{
    OPTICK_EVENT();

    // Start the Dear ImGui frame

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuizmo::BeginFrame();

    // --------------------------------- Here starts the code for the editor ----------------------------------------

    // Manages the docking functionality with the main window
    WindowDockSpaceManagement();

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

            ImGui::SeparatorText("Editor");

            if (ImGui::MenuItem("Save editor configuration")) {



            }

            if (ImGui::MenuItem("Load editor configuration")) {



            }

            ImGui::SeparatorText("Other");

            if (ImGui::MenuItem("Preferences")) {



            }

            ImGui::EndMenu();

        }

        if (ImGui::BeginMenu("View")) {



            ImGui::EndMenu();

        }

        if (ImGui::BeginMenu("GameObject")) {

            if (ImGui::MenuItem("Empty")) {

                GameObject* empty = App->scene->CreateGameObject("Empty", App->scene->mRootNode);
                empty->UID = Random::Generate();

            }

            if (ImGui::BeginMenu("3D Primitives")) {

                if (ImGui::MenuItem("Plane")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Plane.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Plane created successfully");

                }

                if (ImGui::MenuItem("Cube")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Cube.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Cube created successfully");

                }

                if (ImGui::MenuItem("Pyramid")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Pyramid.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Pyramid created successfully");

                }

                if (ImGui::MenuItem("Cylinder")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Cylinder.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Cylinder created successfully");

                }

                if (ImGui::MenuItem("Cone")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Cone.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Cone created successfully");

                }

                if (ImGui::MenuItem("Sphere")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Sphere.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Sphere created successfully");

                }

                if (ImGui::MenuItem("Torus")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Torus.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Torus created successfully");

                }

                if (ImGui::MenuItem("Capsule")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Capsule.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Capsule created successfully");

                }

                if (ImGui::MenuItem("Disc")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Disc.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Disc created successfully");

                }

                if (ImGui::MenuItem("Platonic Solid")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/PlatonicSolid.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Platonic Solid created successfully");

                }

                if (ImGui::MenuItem("Prism")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Prism.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Prism created successfully");

                }

                if (ImGui::MenuItem("Pipe")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Pipe.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Pipe created successfully");

                }

                if (ImGui::MenuItem("Helix")) {

                    App->renderer3D->models.push_back(Model("Assets/Primitives/Helix.fbx"));

                    App->renderer3D->ReloadTextures();

                    LOG("Helix created successfully");

                }

                ImGui::EndMenu();

            }

            ImGui::Separator();

            if (ImGui::MenuItem("Clear Scene")) {

                App->scene->ClearScene();

                LOG("Scene cleared successfully");

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {

            if (ImGui::MenuItem("Application")) {

                showApplication = true;

            }

            if (ImGui::MenuItem("Console")) {

                showConsole = true;

            }

            if (ImGui::MenuItem("Memory Leaks")) {

                showMemoryLeaks = true;



            }

            if (ImGui::MenuItem("Assimp Log")) {

                showAssimpLog = true;

            }

            if (ImGui::MenuItem("Hierarchy")) {

                showHierarchy = true;

            }

            if (ImGui::MenuItem("Inspector")) {

                showInspector = true;

            }

            if (ImGui::MenuItem("Scene")) {

                showScene = true;

            }

            if (ImGui::MenuItem("Game")) {

                showGame = true;

            }

            if (ImGui::MenuItem("Resources")) {

                showResources = true;

            }

            if (ImGui::MenuItem("File Explorer")) {

                showFileExplorer = true;

            }

            if (ImGui::MenuItem("Assets")) {

                showAssets = true;

            }

            if (ImGui::MenuItem("Library")) {

                showLibrary = true;

            }

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

    if (showApplication) {

        if (ImGui::Begin("Application", &showApplication), true) {

            if (ImGui::CollapsingHeader("OpenGL")) {

                // Functions to enable/disable opengl config with checkboxes

                ImGui::Indent(); // Indent to make the checkbox visually nested under the header

                if (ImGui::BeginTable("split", 2))
                {
                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Depth Testing", &gl_DepthTesting)) {

                        Toggle_GL_DepthTesting(gl_DepthTesting);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Face Culling", &gl_FaceCulling)) {

                        Toggle_GL_FaceCulling(gl_FaceCulling);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Lighting", &gl_Lighting)) {

                        Toggle_GL_Lighting(gl_Lighting);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Color Material", &gl_ColorMaterial)) {

                        Toggle_GL_ColorMaterial(gl_ColorMaterial);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Texture Mapping 2D", &gl_TextureMapping2D)) {

                        Toggle_GL_TextureMapping2D(gl_TextureMapping2D);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Texture Mapping 3D", &gl_TextureMapping3D)) {

                        Toggle_GL_TextureMapping3D(gl_TextureMapping3D);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Blending", &gl_Blending)) {

                        Toggle_GL_Blending(gl_Blending);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("MSAA", &gl_MSAA)) {

                        Toggle_GL_MSAA(gl_MSAA);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Stencil Testing", &gl_StencilTesting)) {

                        Toggle_GL_StencilTesting(gl_StencilTesting);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Scissor Testing", &gl_ScissorTesting)) {

                        Toggle_GL_ScissorTesting(gl_ScissorTesting);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Alpha Testing", &gl_AlphaTesting)) {

                        Toggle_GL_AlphaTesting(gl_AlphaTesting);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Point Sprites", &gl_PointSprites)) {

                        Toggle_GL_PointSprites(gl_PointSprites);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Fog", &gl_Fog)) {

                        Toggle_GL_Fog(gl_Fog);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Point Smooth", &gl_PointSmooth)) {

                        Toggle_GL_PointSmooth(gl_PointSmooth);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Line Smooth", &gl_LineSmooth)) {

                        Toggle_GL_LineSmooth(gl_LineSmooth);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Auto Normalization", &gl_Normalization)) {

                        Toggle_GL_Normalization(gl_Normalization);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Polygon Offset", &gl_PolygonOffset)) {

                        Toggle_GL_PolygonOffset(gl_PolygonOffset);

                    }

                    ImGui::TableNextColumn();

                    if (ImGui::Checkbox("Wireframe Mode", &gl_WireframeMode)) {

                        Toggle_GL_WireframeMode(gl_WireframeMode);

                    }

                    ImGui::EndTable();

                }

                ImGui::Unindent(); // Unindent to return to the previous level of indentation

            }

            if (ImGui::CollapsingHeader("Window")) {

                // Window Options

                ImGui::Indent(); // Indent to make the checkbox visually nested under the header

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

            if (ImGui::CollapsingHeader("Renderer3D")) {

                ImGui::Indent(); // Indent to make the checkbox visually nested under the header

                if (ImGui::Checkbox("VSync", &vsync)) {

                    ToggleVSync(vsync);

                }

                ImGui::Unindent(); // Unindent to return to the previous level of indentation

            }

            if (ImGui::CollapsingHeader("Camera3D")) {

                // Camera Options

                ImGui::SeparatorText("POSITION");

                ImGui::BulletText("Camera Position: (%.2f, %.2f, %.2f)", App->camera->editorCamera->GetPos().x, App->camera->editorCamera->GetPos().y, App->camera->editorCamera->GetPos().z);

                ImGui::SeparatorText("ORIENTATION");

                ImGui::BulletText("Camera X: (%.2f, %.2f, %.2f)", App->camera->editorCamera->GetRight().x, App->camera->editorCamera->GetRight().y, App->camera->editorCamera->GetRight().z);
                ImGui::BulletText("Camera Y: (%.2f, %.2f, %.2f)", App->camera->editorCamera->GetUp().x, App->camera->editorCamera->GetUp().y, App->camera->editorCamera->GetUp().z);
                ImGui::BulletText("Camera Z: (%.2f, %.2f, %.2f)", App->camera->editorCamera->GetFront().x, App->camera->editorCamera->GetFront().y, App->camera->editorCamera->GetFront().z);

            }

            if (ImGui::CollapsingHeader("Input")) {

                // Input Options

                ImGuiIO& io = ImGui::GetIO();

                // Mouse Info

                ImGui::SeparatorText("MOUSE");

                if (ImGui::IsMousePosValid()) {

                    ImGui::BulletText("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);

                }
                else {

                    ImGui::BulletText("Mouse pos: <INVALID>");

                }

                ImGui::BulletText("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
                ImGui::BulletText("Mouse down:");

                for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
                ImGui::BulletText("Mouse wheel: %.1f", io.MouseWheel);

                // Keys info

                ImGui::SeparatorText("KEYS");

                struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
                ImGuiKey start_key = (ImGuiKey)0;

                ImGui::BulletText("Keys down:");         for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) { if (funcs::IsLegacyNativeDupe(key) || !ImGui::IsKeyDown(key)) continue; ImGui::SameLine(); ImGui::Text((key < ImGuiKey_NamedKey_BEGIN) ? "\"%s\"" : "\"%s\" %d", ImGui::GetKeyName(key), key); }
                ImGui::BulletText("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
                ImGui::BulletText("Chars queue:");       for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.

            }

            if (ImGui::CollapsingHeader("Editor")) {

                ImGui::Indent(); // Indent to make the checkbox visually nested under the header

                // Light/Dark Mode Checkbox
                if (ImGui::Checkbox("Toggle light mode", &lightMode)) {

                    ToggleLightMode(lightMode);

                }

                // ImGui Demo Window Checkbox
                if (ImGui::Checkbox("Show ImGui demo window", &showImGuiDemo));

                // World Grid Checkbox
                if (ImGui::Checkbox("Show Grid", &App->renderer3D->showGrid));

                ImGui::Unindent(); // Unindent to return to the previous level of indentation

            }

            if (ImGui::CollapsingHeader("Framerate")) {

                // FPS Graph

                char title[50];

                sprintf_s(title, 50, "Framerate (FPS): %.3f", FPSvec[FPSvec.size() - 1]);
                ImGui::PlotHistogram("## Framerate", &FPSvec[0], FPSvec.size(), 0, title, 0.0f, 250.0f, ImVec2(300, 100));

                sprintf_s(title, 50, "DeltaTime (DT): %.3f", DTvec[DTvec.size() - 1]);
                ImGui::PlotHistogram("## DeltaTime", &DTvec[0], DTvec.size(), 0, title, 0.0f, 0.032f, ImVec2(300, 100));

                sprintf_s(title, 50, "Milliseconds (MS): %.3f", MSvec[MSvec.size() - 1]);
                ImGui::PlotHistogram("## Milliseconds", &MSvec[0], MSvec.size(), 0, title, 0.0f, 32.0f, ImVec2(300, 100));

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

            if (ImGui::CollapsingHeader("Meshes")) {

                // 3D Meshes Configuration

                ImGui::Indent(); // Indent to make the checkbox visually nested under the header

                if (ImGui::Checkbox("Show Vertex Normals", &showVertexNormals)) {

                    ToggleMeshesVertexNormals(showVertexNormals);

                }

                if (ImGui::Checkbox("Show Face Normals", &showFaceNormals)) {

                    ToggleMeshesFaceNormals(showFaceNormals);

                }

                if (ImGui::Button("Apply Checker Texture")) {

                    App->renderer3D->ApplyCheckerTexture();

                }

                if (ImGui::Button("Clear Actual Texture")) {

                    App->renderer3D->ClearActualTexture();

                }

                ImGui::Unindent(); // Unindent to return to the previous level of indentation

            }

            ImGui::End();

        }

    }

    if (showConsole) {

        if (ImGui::Begin("Console", &showConsole), true) {

            // Redirect Log Output

            RedirectLogOutput();

            ImGui::End();

        }

    }

    if (showMemoryLeaks) {

        if (ImGui::Begin("Memory Leaks", &showMemoryLeaks), true) {

            // Show Memory Leaks File

            MemoryLeaksOutput();

            ImGui::End();

        }

    }

    if (showAssimpLog) {

        if (ImGui::Begin("Assimp Log", &showAssimpLog), true) {

            // Show Assimp Log File

            AssimpLogOutput();

            ImGui::End();

        }

    }

    if (showHierarchy) {

        if (ImGui::Begin("Hierarchy", &showHierarchy), true) {

            // Show scene hierarchy

            DrawHierarchy();

            ImGui::End();

        }

    }

    if (showInspector) {

        if (ImGui::Begin("Inspector", &showInspector), true) {

            // Show GameObject Inspector

            DrawInspector();

            ImGui::End();

        }

    }

    // END OF APPLICATION MENU

    if (showImGuiDemo) {

        ImGui::ShowDemoWindow();

    }

    if (ImGui::Begin(" ", NULL, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse)) {

        float windowWidth = ImGui::GetWindowWidth();
        float buttonWidth = 50.0f; // Adjust the button width as needed
        float posX = (windowWidth - (3 * buttonWidth + 2 * ImGui::GetStyle().ItemSpacing.x)) * 0.5f;
        ImGui::SetCursorPosX(posX);
        ImGui::Button("Play");
        ImGui::SameLine();
        ImGui::Button("Pause");
        ImGui::SameLine();
        ImGui::Button("Frame");
        ImGui::End();
    }

    if (showAssets) {

        if (ImGui::Begin("Assets", &showAssets), true) {

            DrawAssetsWindow("Assets/");

            // Display the modal when showModal is true
            if (showModal) {

                ImGui::OpenPopup(selectedFilePath.c_str());

                showModal = false;  // Reset the flag

            }

            // Modal window for displaying file contents
            if (ImGui::BeginPopupModal(selectedFilePath.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

                // Read and display the contents of the selected file

                std::ifstream file(selectedFilePath);

                if (file.is_open()) {

                    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                    ImGui::Text("%s", fileContents.c_str());

                    file.close();

                }

                // Close the modal window

                if (ImGui::Button("Close")) {

                    ImGui::CloseCurrentPopup();

                }

                ImGui::EndPopup();
            }

            ImGui::End();
        }

    }

    if (showLibrary) {

        if (ImGui::Begin("Library", &showLibrary), true) {

            DrawLibraryWindow("Library/");

            std::string completeFilePath = selectedFilePath.c_str();
            std::string shortenedFilePath;

            // Find the position of the first "/" in the string
            size_t found = completeFilePath.find("/");

            if (found != std::string::npos) {

                shortenedFilePath = selectedFilePath.substr(found + 1);

            }
            else {

                shortenedFilePath = completeFilePath;

            }

            // Display the modal when showModal is true
            if (showModal) {

                ImGui::OpenPopup(shortenedFilePath.c_str());
                showModal = false;  // Reset the flag

            }

            // Modal window for displaying file contents

            if (ImGui::BeginPopupModal(shortenedFilePath.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

                // Read and display the contents of the selected file

                std::ifstream file(selectedFilePath);

                if (file.is_open()) {

                    std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

                    ImGui::Text("%s", fileContents.c_str());

                    file.close();
                }

                // Close the modal window
                if (ImGui::Button("Close")) {

                    ImGui::CloseCurrentPopup();

                }

                ImGui::EndPopup();
            }

            ImGui::End();
        }

    }

    if (showFileExplorer) {

        if (ImGui::Begin("File Explorer", &showFileExplorer), true) {

            DrawFileExplorer(".");

            ImGui::End();
        }

    }

    if (showResources) {

        if (ImGui::Begin("Resources", &showResources), true) {


            ImGui::End();
        }

    }
    
    if (showGame) {

        if (ImGui::Begin("Game", &showGame), true) {

            // Display the contents of the framebuffer texture
            ImVec2 size = ImGui::GetContentRegionAvail();
            App->scene->gameCameraComponent->SetAspectRatio(size.x / size.y);
            ImGui::Image((ImTextureID)App->scene->gameCameraComponent->framebuffer.TCB, size, ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }

    }

    if (showScene) {

        if (ImGui::Begin("Scene", &showScene), true) {

            // Display the contents of the framebuffer texture
            ImVec2 size = ImGui::GetContentRegionAvail();
            App->camera->editorCamera->SetAspectRatio(size.x / size.y);
            ImGui::Image((ImTextureID)App->camera->editorCamera->framebuffer.TCB, size, ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
        }

    }

    /*float4x4 projection;
    glGetFloatv(GL_PROJECTION_MATRIX, projection.ptr());

    float4x4 view;
    glGetFloatv(GL_MODELVIEW_MATRIX, view.ptr());

    float4x4 model = float4x4::identity;

    ManipulateGizmo(view.ptr(), projection.ptr(), GizmoOperation::TRANSLATE, GizmoMode::LOCAL, model.ptr());*/

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

void ModuleEditor::WindowDockSpaceManagement()
{
    // Set DockSpace Invisible Window Flags
    ImGuiWindowFlags window = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                              ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
                              ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Get Window Viewport
    ImGuiViewport* viewport = ImGui::GetWindowViewport();

    // Set Window Parameters
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

    // Set Window Style Parameters
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    // Begin DockSpace Invisible Window with the flags
    ImGui::Begin("Dockspace", (bool)0, window);

    // Apply Window Style Parameters
    ImGui::PopStyleVar(3);

    // Create DockSpace on the invisible window
    ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    // End DockSpace Window
    ImGui::End();
}

void ModuleEditor::Toggle_GL_DepthTesting(bool depthTesting)
{
    // Allows objects to be rendered based on their depth in the scene, 
    // ensuring that closer objects are rendered in front of farther objects. 

    if (depthTesting) {

        glEnable(GL_DEPTH_TEST);
        LOG("Enabled Depth Testing");

    }
    else {

        glDisable(GL_DEPTH_TEST);
        LOG("Disabled Depth Testing");

    }
}

void ModuleEditor::Toggle_GL_FaceCulling(bool faceCulling)
{
    // Enables the removal of back-facing or front-facing triangles, 
    // which can improve rendering performance.

    if (faceCulling) {

        glEnable(GL_CULL_FACE);
        LOG("Enabled Face Culling");

    }
    else {

        glDisable(GL_CULL_FACE);
        LOG("Disabled Face Culling");

    }
}

void ModuleEditor::Toggle_GL_Lighting(bool lighting)
{
    // Enables OpenGL's lighting and shading capabilities.

    if (lighting) {

        glEnable(GL_LIGHTING);
        LOG("Enabled Lighting");

    }
    else {

        glDisable(GL_LIGHTING);
        LOG("Disabled Lighting");

    }
}

void ModuleEditor::Toggle_GL_ColorMaterial(bool colorMaterial)
{
    // Enables the automatic generation of material properties based on the current color.

    if (colorMaterial) {

        glEnable(GL_COLOR_MATERIAL);
        LOG("Enabled Color Material");

    }
    else {

        glDisable(GL_COLOR_MATERIAL);
        LOG("Disabled Color Material");

    }
}

void ModuleEditor::Toggle_GL_TextureMapping2D(bool textureMapping2D)
{
    // Enables texture mapping for 2D objects. This is essential for applying textures to surfaces.

    if (textureMapping2D) {

        glEnable(GL_TEXTURE_2D);
        App->renderer3D->texturingEnabled = true;
        LOG("Enabled Texture Mapping 2D");

    }
    else {

        glDisable(GL_TEXTURE_2D);
        App->renderer3D->texturingEnabled = false;
        LOG("Disabled Texture Mapping 2D");

    }
}

void ModuleEditor::Toggle_GL_TextureMapping3D(bool textureMapping3D)
{
    // Enables texture mapping for 3D objects.

    if (textureMapping3D) {

        glEnable(GL_TEXTURE_3D);
        LOG("Enabled Texture Mapping 3D");

    }
    else {

        glDisable(GL_TEXTURE_3D);
        LOG("Disabled Texture Mapping 3D");

    }
}

void ModuleEditor::Toggle_GL_Blending(bool blending)
{
    // Enables alpha blending, which is used to create transparency 
    // and translucency effects in your renderings.

    if (blending) {

        glEnable(GL_BLEND);
        LOG("Enabled Blending");

    }
    else {

        glDisable(GL_BLEND);
        LOG("Disabled Blending");

    }
}

void ModuleEditor::Toggle_GL_MSAA(bool msaa)
{
    // Multisampling Anti-Aliasing (MSAA): Provides smoother edges by 
    // sampling multiple points within a pixel.

    if (msaa) {

        glEnable(GL_MULTISAMPLE);
        LOG("Enabled Multisampling Anti-Aliasing (MSAA)");

    }
    else {

        glDisable(GL_MULTISAMPLE);
        LOG("Disabled Multisampling Anti-Aliasing (MSAA)");

    }
}

void ModuleEditor::Toggle_GL_StencilTesting(bool stencilTesting)
{
    // Allows you to perform operations based on stencil values, 
    // which can be used for various effects.

    if (stencilTesting) {

        glEnable(GL_STENCIL_TEST);
        LOG("Enabled Stencil Testing");

    }
    else {

        glDisable(GL_STENCIL_TEST);
        LOG("Disabled Stencil Testing");

    }
}

void ModuleEditor::Toggle_GL_ScissorTesting(bool scissorTesting)
{
    // Clips rendering to a specified rectangular region on the screen.

    if (scissorTesting) {

        glEnable(GL_SCISSOR_TEST);
        LOG("Enabled Scissor Testing");

    }
    else {

        glDisable(GL_SCISSOR_TEST);
        LOG("Disabled Scissor Testing");

    }
}

void ModuleEditor::Toggle_GL_AlphaTesting(bool alphaTesting)
{
    // Enables the discarding of fragments based on an alpha test value. 
    // This can be useful for certain rendering effects.

    if (alphaTesting) {

        glEnable(GL_ALPHA_TEST);
        LOG("Enabled Alpha Testing");

    }
    else {

        glDisable(GL_ALPHA_TEST);
        LOG("Disabled Alpha Testing");

    }
}

void ModuleEditor::Toggle_GL_PointSprites(bool pointSprites)
{
    // Enables rendering points as sprites, which can be textured and have other properties.

    if (pointSprites) {

        glEnable(GL_POINT_SPRITE);
        LOG("Enabled Point Sprites");

    }
    else {

        glDisable(GL_POINT_SPRITE);
        LOG("Disabled Point Sprites");

    }
}

void ModuleEditor::Toggle_GL_Fog(bool fog)
{
    // Enables fog effects in the scene.

    if (fog) {

        glEnable(GL_FOG);
        LOG("Enabled Fog");

    }
    else {

        glDisable(GL_FOG);
        LOG("Disabled Fog");

    }
}

void ModuleEditor::Toggle_GL_PointSmooth(bool pointSmooth)
{
    // Enables point size smoothing, which can make points appear smoother.

    if (pointSmooth) {

        glEnable(GL_POINT_SMOOTH);
        LOG("Enabled Point Smooth");

    }
    else {

        glDisable(GL_POINT_SMOOTH);
        LOG("Disabled Point Smooth");

    }
}

void ModuleEditor::Toggle_GL_LineSmooth(bool lineSmooth)
{
    // Enables line width smoothing for smoother lines.

    if (lineSmooth) {

        glEnable(GL_LINE_SMOOTH);
        LOG("Enabled Line Smooth");

    }
    else {

        glDisable(GL_LINE_SMOOTH);
        LOG("Disabled Line Smooth");

    }
}

void ModuleEditor::Toggle_GL_Normalization(bool normalization)
{
    // Automatically normalizes normals in fixed-function lighting calculations.

    if (normalization) {

        glEnable(GL_NORMALIZE);
        LOG("Enabled Auto Normalization");

    }
    else {

        glDisable(GL_NORMALIZE);
        LOG("Disabled Auto Normalization");

    }
}

void ModuleEditor::Toggle_GL_PolygonOffset(bool polygonOffset)
{
    // Enables the addition of an offset to the depth values of 
    // rendered polygons, useful for avoiding z-fighting.

    if (polygonOffset) {

        glEnable(GL_POLYGON_OFFSET_FILL);
        LOG("Enabled Polygon Offset");

    }
    else {

        glDisable(GL_POLYGON_OFFSET_FILL);
        LOG("Disabled Polygon Offset");

    }
}

void ModuleEditor::Toggle_GL_WireframeMode(bool wireframe)
{
    // Enable or disable wireframe mode for rendering by setting the 
    // polygon mode to either GL_FILL or GL_LINE. When you set it to GL_FILL, 
    // the objects will be rendered as solid surfaces, while setting 
    // it to GL_LINE will render them in wireframe mode.

    if (wireframe) {

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        LOG("Enabled Wireframe Mode");

    }
    else {

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        LOG("Disabled Wireframe Mode");

    }
}

bool ModuleEditor::CleanUp()
{
    bool ret = true;

    LOG("Deleting editor...");

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

void ModuleEditor::ToggleVSync(bool vsync)
{
    if (vsync) {

        SDL_GL_SetSwapInterval(1);

    }
    else {

        SDL_GL_SetSwapInterval(0);

    }
}

void ModuleEditor::ToggleLightMode(bool lightMode)
{
    if (lightMode) {

        ImGui::StyleColorsLight();
        LOG("Enable light mode");

    }
    else {

        ImGui::StyleColorsDark();
        LOG("Enable dark mode");

    }
}

void ModuleEditor::ToggleMeshesVertexNormals(bool showVertexNormals)
{
    for (auto it1 = App->renderer3D->models.begin(); it1 != App->renderer3D->models.end(); ++it1) {
     
        for (auto it2 = (*it1).meshes.begin(); it2 != (*it1).meshes.end(); ++it2) {

            if (showVertexNormals) {

                (*it2).enableVertexNormals = true;

            }
            else {

                (*it2).enableVertexNormals = false;

            }

        }
        
    }

}

void ModuleEditor::ToggleMeshesFaceNormals(bool showFaceNormals)
{
    for (auto it1 = App->renderer3D->models.begin(); it1 != App->renderer3D->models.end(); ++it1) {

        for (auto it2 = (*it1).meshes.begin(); it2 != (*it1).meshes.end(); ++it2) {

            if (showFaceNormals) {

                (*it2).enableFaceNormals = true;

            }
            else {

                (*it2).enableFaceNormals = false;

            }

        }

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
    const GLubyte* vendor = glGetString(GL_VENDOR);
    ImGui::Text("Vendor:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", vendor);

    const GLubyte* renderer = glGetString(GL_RENDERER);
    ImGui::Text("GPU:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", renderer);

    const GLubyte* version = glGetString(GL_VERSION);
    ImGui::Text("OpenGL version supported:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", version);

    const GLubyte* glsl = glGetString(GL_SHADING_LANGUAGE_VERSION);
    ImGui::Text("GLSL:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glsl);

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
    ImGui::Text("Ymir Engine v0.1");

    ImGui::NewLine();

    ImGui::SeparatorText("DESCRIPTION");
    ImGui::NewLine();

    const char* engineInfo = "Ymir Engine is part of the Game Engines subject, on the third year of the\nVideogame Design and Development degree, taught at CITM UPC (Terrassa)\nand supervised by Miquel Suau.\n\nThe engine has been made from scratch in C++ using SDL and OpenGL to manage\ngraphics. The main target of the project is to be able to integrate complex\nsystems such as graphics management and game engine architecture in a simple\nand understandable way for educational purposes.";

    ImGui::Text("%s", engineInfo);

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

    SDL_version version;
    SDL_GetVersion(&version);
    
    ImGui::BulletText("SDL v%d.%d.%d -> ", version.major, version.minor, version.patch);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/libsdl-org/SDL");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/libsdl-org/SDL");

    }

    ImGui::BulletText("OpenGL v%s ->", glGetString(GL_VERSION));
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://www.opengl.org/");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://www.opengl.org/");

    }

    ImGui::BulletText("Glew v%s ->", glewGetString(GLEW_VERSION));
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/nigels-com/glew");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/nigels-com/glew");

    }

    ImGui::BulletText("ImGui v%s ->", IMGUI_VERSION);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/ocornut/imgui");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/ocornut/imgui");

    }

    ImGui::BulletText("Assimp v%d.%d.%d ->", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/assimp/assimp");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/assimp/assimp");

    }

    ILint ILversion = ilGetInteger(IL_VERSION_NUM);

    uint ILmajor = (ILversion / 100) % 10;
    uint ILminor = ILversion % 100;

    ImGui::BulletText("DevIL v%d.%d ->", ILmajor, ILminor);
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://openil.sourceforge.net/download.php");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://openil.sourceforge.net/download.php");

    }

    ImGui::BulletText("MathGeoLib ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/juj/MathGeoLib");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/juj/MathGeoLib");

    }

    ImGui::BulletText("Optick ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://github.com/bombomby/optick");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://github.com/bombomby/optick");

    }

    ImGui::BulletText("mmgr ->");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.0f, 0.5f, 1.0f, 1.0f), "https://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");
    if (ImGui::IsItemClicked()) {

        RequestBrowser("https://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");

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
    for (auto it = Log::debugStrings.begin(); it != Log::debugStrings.end(); ++it) {

        ImGui::Text((*it).c_str());
        
    }
}

void ModuleEditor::MemoryLeaksOutput()
{
    ImGui::TextWrapped("%s", memleaksFileContents.c_str());
}

void ModuleEditor::AssimpLogOutput()
{
    ImGui::TextWrapped("%s", AssimpLogFileContents.c_str());
}

void ModuleEditor::DrawHierarchy()
{
    CreateHierarchyTree(App->scene->mRootNode);
}

void ModuleEditor::CreateHierarchyTree(GameObject* node)
{
    if (node != nullptr) {

        // Set flags to open the tree nodes
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | (node->selected ? ImGuiTreeNodeFlags_Selected : 0);

        if (!node->active) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.4f));

        bool isNodeOpen = ImGui::TreeNodeEx(node->name.c_str(), flags);

        if (!node->active) ImGui::PopStyleColor();

        if (ImGui::IsItemClicked()) {

            node->selected = true; // Toggle the selected state when clicked

            for (auto it = App->scene->gameObjects.begin(); it != App->scene->gameObjects.end(); ++it) {

                if ((*it) != node) {

                    (*it)->selected = false;

                }

            }

        }

        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("GameObject", node, sizeof(GameObject*));

            draggedGO = node;
            ImGui::Text("Drag to");
            ImGui::EndDragDropSource();
        }

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
        {
            hoveredGO = node;
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject")) {

                draggedGO->SetParent(hoveredGO);
            }
            ImGui::EndDragDropTarget();
        }

        if (ImGui::IsItemClicked(1)) {

            ImGui::OpenPopup("DeleteGameObject");

        }

        if (ImGui::BeginPopupContextItem()) {

            if (ImGui::MenuItem("Delete")) {

                if (node != App->scene->mRootNode && node->selected) {

                    // This should be reworked for the next delivery (A2)

                    App->editor->DestroyHierarchyTree(node);

                    App->renderer3D->models.erase(
                        std::remove_if(App->renderer3D->models.begin(), App->renderer3D->models.end(),
                            [](const Model& model) { return model.modelGO->selected; }
                        ),
                        App->renderer3D->models.end()
                    );

                    for (auto it = App->renderer3D->models.begin(); it != App->renderer3D->models.end(); ++it) {
                        // Check if the entire model is selected
                        if ((*it).modelGO->selected) {

                            it = App->renderer3D->models.erase(it); // Remove the entire model

                        }
                        else {
                            // If the model is not selected, check its meshes
                            auto& meshes = it->meshes; // Assuming 'meshes' is the vector of meshes inside the 'Model'

                            meshes.erase(
                                std::remove_if(meshes.begin(), meshes.end(),
                                    [](const Mesh& mesh) { return mesh.meshGO->selected; }
                                ),
                                meshes.end()
                            );
                        }
                    }

                    App->scene->gameObjects.erase(
                        std::remove_if(App->scene->gameObjects.begin(), App->scene->gameObjects.end(),
                            [](const GameObject* obj) { return obj->selected; }
                        ),
                        App->scene->gameObjects.end()
                    );

                    for (auto it = App->scene->gameObjects.begin(); it != App->scene->gameObjects.end(); ++it) {

                        (*it)->selected = false;

                    }

                    delete node;
                    node = nullptr;

                }
                else if (node == App->scene->mRootNode && node->selected) {

                    App->scene->ClearScene();

                }

            }

            if (ImGui::MenuItem("Create Empty Children")) {

                GameObject* empty = App->scene->CreateGameObject("Empty", node);
                empty->UID = Random::Generate();

            }

            ImGui::EndPopup();
        }

        if (isNodeOpen)
        {
            // Display the children if the node is open

            if (node != nullptr) {

                if (node->mChildren.size())
                {
                    for (uint i = 0; i < node->mChildren.size(); i++)
                    {
                        CreateHierarchyTree(node->mChildren[i]);
                    }
                }

            }

            // Close the TreeNode when you're done with its children
            ImGui::TreePop();
        }

    }

}

void ModuleEditor::DestroyHierarchyTree(GameObject* node)
{
    if (node == nullptr) {
        return;
    }

    App->scene->DestroyGameObject(node);

}

void ModuleEditor::DrawInspector()
{
    for (auto it = App->scene->gameObjects.begin(); it != App->scene->gameObjects.end(); ++it) {

        if ((*it) != nullptr) {

            if ((*it)->selected) {

                ImGui::Checkbox(" Active   ", &(*it)->active);
                ImGui::SameLine();
                char nameBuffer[256]; // You can adjust the buffer size as needed

                // Copy the current name to the buffer
                strcpy(nameBuffer, (*it)->name.c_str());

                // Create an input text field in your ImGui window
                if (ImGui::InputText(" ", nameBuffer, sizeof(nameBuffer)))
                {
                    // The input text has changed, update the name
                    (*it)->name = nameBuffer;
                }

                ImGui::Spacing();

                ImGui::Text("UID: %d", (*it)->UID);

                ImGui::Spacing();

                Component* transform = (*it)->GetComponent(ComponentType::TRANSFORM);
                Component* mesh = (*it)->GetComponent(ComponentType::MESH);
                Component* material = (*it)->GetComponent(ComponentType::MATERIAL);
                Component* camera = (*it)->GetComponent(ComponentType::CAMERA);

                if (transform != nullptr) transform->OnInspector(); ImGui::Spacing();
                if (mesh != nullptr) mesh->OnInspector(); ImGui::Spacing();
                if (material != nullptr) material->OnInspector(); ImGui::Spacing();
                if (camera != nullptr) camera->OnInspector(); ImGui::Spacing();

                float buttonWidth = 120.0f;  // Adjust the width as needed
                float windowWidth = ImGui::GetWindowWidth();
                float xPos = (windowWidth - buttonWidth) * 0.5f;

                // Set the cursor position to center the button within the menu
                ImGui::SetCursorPosX(xPos);

                ImGui::Button("Add Component");

            }

        }

    }

}

void ModuleEditor::ManipulateGizmo(const float* viewMatrix, const float* projectionMatrix, GizmoOperation operation, GizmoMode mode, float* modelMatrix, float* deltaMatrix, float* snap)
{
    ImGuizmo::Manipulate(viewMatrix, projectionMatrix, ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::WORLD, modelMatrix);
}

void ModuleEditor::DrawFileExplorer(const std::string& rootFolder) {

    // Process Directories First

    for (const auto& entry : std::filesystem::directory_iterator(rootFolder)) {

        if (entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                if (ImGui::TreeNodeEx(entryName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) {

                    DrawFileExplorer(entry.path().string());

                    ImGui::TreePop();

                }

            }

        }

    }

    // Process Files Afterwards

    for (const auto& entry : std::filesystem::directory_iterator(rootFolder)) {

        if (!entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                ImGui::Selectable(entryName.c_str());

            }

        }

    }

}

void ModuleEditor::DrawAssetsWindow(const std::string& assetsFolder) {

    // Process Directories First

    for (const auto& entry : std::filesystem::directory_iterator(assetsFolder)) {

        if (entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.3f, 1.0f));

                if (ImGui::TreeNodeEx(entryName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) {

                    DrawAssetsWindow(entry.path().string());

                    ImGui::TreePop();

                }

                ImGui::PopStyleColor();

            }

        }

    }

    // Process Files Afterwards

    for (const auto& entry : std::filesystem::directory_iterator(assetsFolder)) {

        if (!entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                if ((entryName.find(".meta") != std::string::npos) || 
                    (entryName.find(".glsl") != std::string::npos) ||
                    (entryName.find(".json") != std::string::npos)) {

                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.6f, 0.6f, 1.0f)); 

                    if (ImGui::Selectable(entryName.c_str())) {

                        selectedFilePath = entry.path().string();
                        showModal = true;  // Set the flag to open the modal
                    }

                    ImGui::PopStyleColor();

                }
                else {

                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                    ImGui::Selectable(entryName.c_str());

                    ImGui::PopStyleColor();

                }

            }

        }

    }

}

void ModuleEditor::DrawLibraryWindow(const std::string& libraryFolder) {

    // Process Directories First

    for (const auto& entry : std::filesystem::directory_iterator(libraryFolder)) {

        if (entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.3f, 1.0f));

                if (ImGui::TreeNodeEx(entryName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) {

                    DrawLibraryWindow(entry.path().string());

                    ImGui::TreePop();

                }

                ImGui::PopStyleColor();

            }

        }

    }

    // Process Files Afterwards

    for (const auto& entry : std::filesystem::directory_iterator(libraryFolder)) {

        if (!entry.is_directory()) {

            std::string entryName = entry.path().filename().string();

            if (entryName != "." && entryName != "..") {

                if ((entryName.find(".yscene") != std::string::npos) || 
                    (entryName.find(".ymodel") != std::string::npos) ||
                    (entryName.find(".json") != std::string::npos)) {

                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.2f, 0.6f, 0.6f, 1.0f));

                    if (ImGui::Selectable(entryName.c_str())) {

                        selectedFilePath = entry.path().string();
                        showModal = true;  // Set the flag to open the modal
                    }

                    ImGui::PopStyleColor();

                }
                else {

                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                    ImGui::Selectable(entryName.c_str());

                    ImGui::PopStyleColor();

                }

            }

        }

    }

}
