//===-- LoopConvert/VariableNaming.h - Gererate variable names --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the definitino of the VariableNamer class, which
/// is responsible for generating new variable names and ensuring that they do
/// not conflict with existing ones.
///
//===----------------------------------------------------------------------===//
#include "VariableNaming.h"

using namespace llvm;
using namespace clang;

std::string VariableNamer::createIndexName() {
  // FIXME: Add in naming conventions to handle:
  //  - Uppercase/lowercase indices
  //  - How to handle conflicts
  //  - An interactive process for naming
  std::string IteratorName;
  std::string ContainerName;
  if (TheContainer)
    ContainerName = TheContainer->getName().str();

  size_t Len = ContainerName.length();
  if (Len > 1 && ContainerName[Len - 1] == 's')
    IteratorName = ContainerName.substr(0, Len - 1);
  else
    IteratorName = "elem";

  if (!declarationExists(IteratorName))
    return IteratorName;

  IteratorName = ContainerName + "_" + OldIndex->getName().str();
  if (!declarationExists(IteratorName))
    return IteratorName;

  IteratorName = ContainerName + "_elem";
  if (!declarationExists(IteratorName))
    return IteratorName;

  IteratorName += "_elem";
  if (!declarationExists(IteratorName))
    return IteratorName;

  IteratorName = "_elem_";

  // Someone defeated my naming scheme...
  while (declarationExists(IteratorName))
    IteratorName += "i";
  return IteratorName;
}

/// \brief Determines whether or not the the name \a Symbol conflicts with
/// language keywords or defined macros. Also checks if the name exists in
/// LoopContext, any of its parent contexts, or any of its child statements.
///
/// We also check to see if the same identifier was generated by this loop
/// converter in a loop nested within SourceStmt.
bool VariableNamer::declarationExists(StringRef Symbol) {
  assert(Context != 0 && "Expected an ASTContext");
  IdentifierInfo &Ident = Context->Idents.get(Symbol);

  // Check if the symbol is not an identifier (ie. is a keyword or alias).
  if (!isAnyIdentifier(Ident.getTokenID()))
    return true;

  // Check for conflicting macro definitions.
  if (Ident.hasMacroDefinition())
    return true;

  // Determine if the symbol was generated in a parent context.
  for (const Stmt *S = SourceStmt; S != NULL; S = ReverseAST->lookup(S)) {
    StmtGeneratedVarNameMap::const_iterator I = GeneratedDecls->find(S);
    if (I != GeneratedDecls->end() && I->second == Symbol)
      return true;
  }

  // FIXME: Rather than detecting conflicts at their usages, we should check the
  // parent context.
  // For some reason, lookup() always returns the pair (NULL, NULL) because its
  // StoredDeclsMap is not initialized (i.e. LookupPtr.getInt() is false inside
  // of DeclContext::lookup()). Why is this?

  // Finally, determine if the symbol was used in the loop or a child context.
  DeclFinderASTVisitor DeclFinder(Symbol, GeneratedDecls);
  return DeclFinder.findUsages(SourceStmt);
}