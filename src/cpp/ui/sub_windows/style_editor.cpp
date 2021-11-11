#include "style_editor.h"

#include <iostream>

namespace UI {

PYBIND11_EMBEDDED_MODULE(imgui_style, m) {
    m.def("get_style", [](){
        ImGuiStyle& s = ImGui::GetStyle();
        return style_save_dict(&s);
    });

    m.def("set_style", [](py::dict d){
        ImGuiStyle& s = ImGui::GetStyle();
        style_load_dict(&s, d);
    });
}

py::dict style_save_dict(ImGuiStyle* s) {
    py::dict d;

    d["Alpha"] = s->Alpha;
    d["DisabledAlpha"] = s->DisabledAlpha;

    py::list WindowPadding_list = py::list();
    WindowPadding_list.append(s->WindowPadding.x);
    WindowPadding_list.append(s->WindowPadding.y);
    d["WindowPadding"] = WindowPadding_list;

    d["WindowRounding"] = s->WindowRounding;
    d["WindowBorderSize"] = s->WindowBorderSize;

    py::list WindowMinSize_list = py::list();
    WindowMinSize_list.append(s->WindowMinSize.x);
    WindowMinSize_list.append(s->WindowMinSize.y);
    d["WindowMinSize"] = WindowMinSize_list;

    py::list WindowTitleAlign_list = py::list();
    WindowTitleAlign_list.append(s->WindowTitleAlign.x);
    WindowTitleAlign_list.append(s->WindowTitleAlign.y);
    d["WindowTitleAlign"] = WindowTitleAlign_list;

    d["WindowMenuButtonPosition"] = (int)s->WindowMenuButtonPosition;
    d["ChildRounding"] = s->ChildRounding;
    d["ChildBorderSize"] = s->ChildBorderSize;
    d["PopupRounding"] = s->PopupRounding;
    d["PopupBorderSize"] = s->PopupBorderSize;

    py::list FramePadding_list = py::list();
    FramePadding_list.append(s->FramePadding.x);
    FramePadding_list.append(s->FramePadding.y);
    d["FramePadding"] = FramePadding_list;

    d["FrameRounding"] = s->FrameRounding;
    d["FrameBorderSize"] = s->FrameBorderSize;

    py::list ItemSpacing_list = py::list();
    ItemSpacing_list.append(s->ItemSpacing.x);
    ItemSpacing_list.append(s->ItemSpacing.y);
    d["ItemSpacing"] = ItemSpacing_list;

    py::list ItemInnerSpacing_list = py::list();
    ItemInnerSpacing_list.append(s->ItemInnerSpacing.x);
    ItemInnerSpacing_list.append(s->ItemInnerSpacing.y);
    d["ItemInnerSpacing"] = ItemInnerSpacing_list;

    py::list CellPadding_list = py::list();
    CellPadding_list.append(s->CellPadding.x);
    CellPadding_list.append(s->CellPadding.y);
    d["CellPadding"] = CellPadding_list;

    py::list TouchExtraPadding_list = py::list();
    TouchExtraPadding_list.append(s->TouchExtraPadding.x);
    TouchExtraPadding_list.append(s->TouchExtraPadding.y);
    d["TouchExtraPadding"] = TouchExtraPadding_list;

    d["IndentSpacing"] = s->IndentSpacing;
    d["ColumnsMinSpacing"] = s->ColumnsMinSpacing;
    d["ScrollbarSize"] = s->ScrollbarSize;
    d["ScrollbarRounding"] = s->ScrollbarRounding;
    d["GrabMinSize"] = s->GrabMinSize;
    d["GrabRounding"] = s->GrabRounding;
    d["LogSliderDeadzone"] = s->LogSliderDeadzone;
    d["TabRounding"] = s->TabRounding;
    d["TabBorderSize"] = s->TabBorderSize;
    d["TabMinWidthForCloseButton"] = s->TabMinWidthForCloseButton;
    d["ColorButtonPosition"] = (int)s->ColorButtonPosition;

    py::list ButtonTextAlign_list = py::list();
    ButtonTextAlign_list.append(s->ButtonTextAlign.x);
    ButtonTextAlign_list.append(s->ButtonTextAlign.y);
    d["ButtonTextAlign"] = ButtonTextAlign_list;

    py::list SelectableTextAlign_list = py::list();
    SelectableTextAlign_list.append(s->SelectableTextAlign.x);
    SelectableTextAlign_list.append(s->SelectableTextAlign.y);
    d["SelectableTextAlign"] = SelectableTextAlign_list;

    py::list DisplayWindowPadding_list = py::list();
    DisplayWindowPadding_list.append(s->DisplayWindowPadding.x);
    DisplayWindowPadding_list.append(s->DisplayWindowPadding.y);
    d["DisplayWindowPadding"] = DisplayWindowPadding_list;

    py::list DisplaySafeAreaPadding_list = py::list();
    DisplaySafeAreaPadding_list.append(s->DisplaySafeAreaPadding.x);
    DisplaySafeAreaPadding_list.append(s->DisplaySafeAreaPadding.y);
    d["DisplaySafeAreaPadding"] = DisplaySafeAreaPadding_list;

    d["MouseCursorScale"] = s->MouseCursorScale;
    d["AntiAliasedLines"] = s->AntiAliasedLines;
    d["AntiAliasedLinesUseTex"] = s->AntiAliasedLinesUseTex;
    d["AntiAliasedFill"] = s->AntiAliasedFill;
    d["CurveTessellationTol"] = s->CurveTessellationTol;
    d["CircleTessellationMaxError"] = s->CircleTessellationMaxError;

    // Saving Colors:
    py::list colors = py::list();
    for (int i = 0; i < (int)ImGuiCol_COUNT; i++) {
        py::list new_color;
        new_color.append(s->Colors[i].w);
        new_color.append(s->Colors[i].x);
        new_color.append(s->Colors[i].y);
        new_color.append(s->Colors[i].z);

        colors.append(new_color);
    }

    d["_Colors"] = colors;

    return d;
}

void style_load_dict(ImGuiStyle* s, py::dict d) {
    if (d.empty()){
        return;
    }

    s->Alpha = d["Alpha"].cast<float>();
    s->DisabledAlpha = d["DisabledAlpha"].cast<float>();

    s->WindowPadding = ImVec2(
        ((py::list)d["WindowPadding"])[1].cast<float>(),
        ((py::list)d["WindowPadding"])[1].cast<float>());

    s->WindowRounding = d["WindowRounding"].cast<float>();
    s->WindowBorderSize = d["WindowBorderSize"].cast<float>();

    s->WindowMinSize = ImVec2(
        ((py::list)d["WindowMinSize"])[1].cast<float>(),
        ((py::list)d["WindowMinSize"])[1].cast<float>());

    s->WindowTitleAlign = ImVec2(
        ((py::list)d["WindowTitleAlign"])[1].cast<float>(),
        ((py::list)d["WindowTitleAlign"])[1].cast<float>());

    s->WindowMenuButtonPosition = (ImGuiDir)d["WindowMenuButtonPosition"].cast<int>();
    s->ChildRounding = d["ChildRounding"].cast<float>();
    s->ChildBorderSize = d["ChildBorderSize"].cast<float>();
    s->PopupRounding = d["PopupRounding"].cast<float>();
    s->PopupBorderSize = d["PopupBorderSize"].cast<float>();

    s->FramePadding = ImVec2(
        ((py::list)d["FramePadding"])[1].cast<float>(),
        ((py::list)d["FramePadding"])[1].cast<float>());

    s->FrameRounding = d["FrameRounding"].cast<float>();
    s->FrameBorderSize = d["FrameBorderSize"].cast<float>();

    s->ItemSpacing = ImVec2(
        ((py::list)d["ItemSpacing"])[1].cast<float>(),
        ((py::list)d["ItemSpacing"])[1].cast<float>());

    s->ItemInnerSpacing = ImVec2(
        ((py::list)d["ItemInnerSpacing"])[1].cast<float>(),
        ((py::list)d["ItemInnerSpacing"])[1].cast<float>());

    s->CellPadding = ImVec2(
        ((py::list)d["CellPadding"])[1].cast<float>(),
        ((py::list)d["CellPadding"])[1].cast<float>());

    s->TouchExtraPadding = ImVec2(
        ((py::list)d["TouchExtraPadding"])[1].cast<float>(),
        ((py::list)d["TouchExtraPadding"])[1].cast<float>());

    s->IndentSpacing = d["IndentSpacing"].cast<float>();
    s->ColumnsMinSpacing = d["ColumnsMinSpacing"].cast<float>();
    s->ScrollbarSize = d["ScrollbarSize"].cast<float>();
    s->ScrollbarRounding = d["ScrollbarRounding"].cast<float>();
    s->GrabMinSize = d["GrabMinSize"].cast<float>();
    s->GrabRounding = d["GrabRounding"].cast<float>();
    s->LogSliderDeadzone = d["LogSliderDeadzone"].cast<float>();
    s->TabRounding = d["TabRounding"].cast<float>();
    s->TabBorderSize = d["TabBorderSize"].cast<float>();
    s->TabMinWidthForCloseButton = d["TabMinWidthForCloseButton"].cast<float>();
    s->ColorButtonPosition = (ImGuiDir)d["ColorButtonPosition"].cast<int>();

    s->ButtonTextAlign = ImVec2(
        ((py::list)d["ButtonTextAlign"])[1].cast<float>(),
        ((py::list)d["ButtonTextAlign"])[1].cast<float>());

    s->SelectableTextAlign = ImVec2(
        ((py::list)d["SelectableTextAlign"])[1].cast<float>(),
        ((py::list)d["SelectableTextAlign"])[1].cast<float>());

    s->DisplayWindowPadding = ImVec2(
        ((py::list)d["DisplayWindowPadding"])[1].cast<float>(),
        ((py::list)d["DisplayWindowPadding"])[1].cast<float>());

    s->DisplaySafeAreaPadding = ImVec2(
        ((py::list)d["DisplaySafeAreaPadding"])[1].cast<float>(),
        ((py::list)d["DisplaySafeAreaPadding"])[1].cast<float>());

    s->MouseCursorScale = d["MouseCursorScale"].cast<float>();
    s->AntiAliasedLines = d["AntiAliasedLines"].cast<bool>();
    s->AntiAliasedLinesUseTex = d["AntiAliasedLinesUseTex"].cast<bool>();
    s->AntiAliasedFill = d["AntiAliasedFill"].cast<bool>();
    s->CurveTessellationTol = d["CurveTessellationTol"].cast<float>();
    s->CircleTessellationMaxError = d["CircleTessellationMaxError"].cast<float>();

    // Loading Colors:
    py::list colors = d["_Colors"];
    // std::cout << "colors = " << py::str(colors).cast<std::string>() << std::endl;
    for (int i = 0; i < (int)ImGuiCol_COUNT; i++) {
        py::list color = colors[i];
        
        s->Colors[i].w = color[0].cast<float>();
        s->Colors[i].x = color[1].cast<float>();
        s->Colors[i].y = color[2].cast<float>();
        s->Colors[i].z = color[3].cast<float>();
    }
}


void save_style() {
    ImGuiStyle& s = ImGui::GetStyle();
    py::gil_scoped_acquire gil;
    py::module_ style_mod = py::module_::import("style_helper");
    style_mod.attr("save_style_dict")(style_save_dict(&s));
}

void load_style() {
    ImGuiStyle& s = ImGui::GetStyle();
    py::gil_scoped_acquire gil;
    py::module_ style_mod = py::module_::import("style_helper");
    style_load_dict(&s, style_mod.attr("load_style_dict")());
}

void StyleEditor::onDraw() {

    if (ImGui::Button("Load Style")) {
        load_style();
    }

    ImGui::SameLine();
    if (ImGui::Button("Save Style")) {
        save_style();
    }

    ImGui::Separator();
    ImGui::ShowStyleEditor();
}
}


