set(SOURCES
	imgui.h
	imgui_internal.h
	imgui-SFML.h
	imgui-SFML_export.h
	imgui_user.h
	imgui_user.inl
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	
	imgui.cpp
	imgui_tables.cpp
	imgui_draw.cpp
	imgui_widgets.cpp
	imgui-SFML.cpp
	imgui_demo.cpp

	widgets/timeline.h
	widgets/timeline.inl
)

target_sources(${ENGINE_PROJECT} PUBLIC 
	${SOURCES}
)
