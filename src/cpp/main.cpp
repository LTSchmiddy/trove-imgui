// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "main.h"
#include <iostream>
#include <stb_image.h>

#include "ui/main_window.h"
#include "ui/main_menu_bar.h"
#include "python/py_main.h"


AppGlobal APP_GLOBAL = {};

void init_vlc() {
    std::cout << "Loading VLC..." << std::endl;
    std::cout << "LibVLC was compiled with: " << libvlc_get_compiler() << std::endl;
    const char* vlcArgs[] = {
        "-vv",
        "--config=./vlc-config.cfg"
    };
    APP_GLOBAL.vlc = new VLC::Instance(2, vlcArgs);
}

// Main code
int main(int, char**)
{
    // Initialize Python Interpreter:
    std::cout << "\n\n\n ===== Trove - Begin Log: ===== "  << std::endl;
    if (!init_python()) {
        std::cerr << "FATAL ERROR: Python interpreter failed to load. Trove is exiting..." << std::endl;
        return -1;
    }

    // Load VLC
    init_vlc();

    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    
    std::cout << "Starting UI..." << std::endl;
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Trove", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    APP_GLOBAL.gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, APP_GLOBAL.gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    APP_GLOBAL.window = window;
    // Set up fps timer:


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, APP_GLOBAL.gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
   
    // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    UI::MainWindow* main_window = new UI::MainWindow();
    APP_GLOBAL.fragments.emplace_back(main_window);

    // Releasing the GIL from this thread. We need this if we're gonna use threads on the Python side.
    // This also means that whenever we want to access the Python interpreter during the main loop,
    // we'll need to re-aquire the GIL manually, using PyGILState_Ensure() and PyGILState_Release().
    Py_BEGIN_ALLOW_THREADS;

    // Main loop
    bool done = false;
    while (!done)
    {   
        
        // Starts the frame timer:
        int frame_start = SDL_GetTicks();
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            
            // Allows fragments to consume events:
            bool consumed = false;
            for (int i = 0; i < APP_GLOBAL.fragments.size(); i++) {
                auto fragment = APP_GLOBAL.fragments.at(i);
                
                if (fragment->onEvent(&event)) {
                    consumed = true;
                    break;
                }
            }
            if (consumed) {
                continue;
            }

            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            
        }

        if (done == true) {
            break;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        construct_menu_bar();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (APP_GLOBAL.show_demo_window) {
            ImGui::ShowDemoWindow(&APP_GLOBAL.show_demo_window);
        }

        // Background Tasks:
        for (int i = 0; i < APP_GLOBAL.fragments.size(); i++) {
            auto fragment = APP_GLOBAL.fragments.at(i);
            fragment->onBackground();
        }

        for (int i = 0; i < APP_GLOBAL.fragments.size(); i++) {
            auto fragment = APP_GLOBAL.fragments.at(i);
            if (fragment->should_draw) {
                fragment->onDraw();
            }
        }
        // Before we render, we want to cap the frame rate, so that our cpu usage doesn't run wild:
        int frame_end = SDL_GetTicks();
        int delay_interval = (1000/APP_GLOBAL.target_fps) - (frame_end - frame_start);
        if (delay_interval > 0) {
            SDL_Delay(delay_interval);      
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);  
    }

    // Resuming control of the GIL for finalization:
    Py_END_ALLOW_THREADS;   
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    for (int i = 0; i < APP_GLOBAL.fragments.size(); i++) {
        auto fragment = APP_GLOBAL.fragments.at(i);
        if (fragment->delete_during_cleanup){
            delete fragment;
        }
    }

    SDL_GL_DeleteContext(APP_GLOBAL.gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    delete APP_GLOBAL.vlc;
    shutdown_python();
    return 0;
}