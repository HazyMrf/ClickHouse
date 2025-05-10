#include <Storages/Model.h>
#include <Parsers/ASTModelDeclaration.h>
#include <Parsers/ASTLiteral.h>

namespace DB
{

Model Model::getTableModelFromAST(
    const ASTPtr & definition_ast, [[maybe_unused]] const ColumnsDescription & columns, [[maybe_unused]] ContextPtr context) {

    Model model;
    model.definition_ast = definition_ast->clone();

    const auto * model_decl = definition_ast->as<ASTModelDeclaration>();
    model.name = model_decl->name;

    const auto * target_column = model_decl->target_column->as<ASTLiteral>();
    model.target_column = target_column->value.safeGet<String>();

    const auto * algorithm = model_decl->algorithm->as<ASTLiteral>();
    model.algorithm = algorithm->value.safeGet<String>();

    return model;
}

}
