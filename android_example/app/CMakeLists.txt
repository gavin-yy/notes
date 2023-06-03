
add_library(mycjni SHARED src/main/jni/mycjni.c)

target_link_libraries(mycjni log)