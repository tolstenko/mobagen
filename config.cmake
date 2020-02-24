#hunter_config(glm VERSION 0.9.8)
hunter_config(
        CURL
        VERSION ${HUNTER_CURL_VERSION}
        CMAKE_ARGS CMAKE_USE_BORINGSSL=ON
)