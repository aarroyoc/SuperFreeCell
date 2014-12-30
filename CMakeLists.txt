PROJECT(SuperFreeCell)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(SuperFreeCell_SRC
"src/App.cpp"
"src/Window.cpp"
"src/GameView.cpp"
"src/Card.cpp"
)

ADD_EXECUTABLE(SuperFreeCell ${SuperFreeCell_SRC})
TARGET_LINK_LIBRARIES(SuperFreeCell be root tracker translation)
ADD_CUSTOM_COMMAND(TARGET SuperFreeCell COMMAND rc -o SuperFreeCell.rsrc ${CMAKE_CURRENT_SOURCE_DIR}/src/SuperFreeCell.rdef COMMENT "Compiling resources")
ADD_CUSTOM_COMMAND(TARGET SuperFreeCell COMMAND xres -o SuperFreeCell SuperFreeCell.rsrc COMMENT "Adding resources to executable")
ADD_CUSTOM_COMMAND(TARGET SuperFreeCell COMMAND mimeset --all SuperFreeCell COMMENT "Adjusting MIME types")
