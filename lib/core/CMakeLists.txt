include_directories(
    ${XRAY_SOURCE_DIR}/third_party/llvm/include
    ${XRAY_BINARY_DIR}/third_party/llvm/include
    ${XRAY_SOURCE_DIR}/third_party/llvm/tools/clang/include
    ${XRAY_BINARY_DIR}/third_party/llvm/tools/clang/include)

add_definitions(
    -D__STDC_LIMIT_MACROS
    -D__STDC_CONSTANT_MACROS
    )

set(LLVM_LINK_COMPONENTS
  asmparser
  bitreader
  support
  mc
  )

add_llvm_tool(xray-core
  main.cc
  )

target_link_libraries(xray-core
  clangTooling
  clangBasic
  clangRewriteFrontend
  )

install(TARGETS xray-core
  RUNTIME DESTINATION bin)
