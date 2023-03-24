set(SOURCES
	imgui.h
	imgui_internal.h
	imgui-SFML.h
	imgui-SFML_export.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	
	imgui.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	imgui-SFML.cpp
	imgui_demo.cpp
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
