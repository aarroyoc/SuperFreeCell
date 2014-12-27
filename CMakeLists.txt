PROJECT(SuperFreeCell)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(SuperFreeCell_SRC
"src/App.cpp"
"src/Window.cpp"
"src/GameView.cpp"
)

ADD_EXECUTABLE(SuperFreeCell ${SuperFreeCell_SRC})
TARGET_LINK_LIBRARIES(SuperFreeCell be root tracker)
