#include <clang/AST/ASTConsumer.h>
#include <clang/Driver/Options.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Rewrite/Frontend/FixItRewriter.h>
#include <clang/Rewrite/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/Signals.h>

#include <iostream>

int main(int argc, char** argv) {
  std::cout << "HELLO" << std::endl;
  return 0;
}
