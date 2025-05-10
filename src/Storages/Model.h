#pragma once

#include <Parsers/IAST_fwd.h>
#include <Storages/DataDestinationType.h>
#include <Storages/ColumnsDescription.h>
#include <Storages/KeyDescription.h>
#include <Interpreters/AggregateDescription.h>
#include <Storages/TTLMode.h>

namespace DB
{

/// Table ML model.
struct Model
{
    /// Definition. Include all parts of MODEL:
    /// ADD/DROP MODEL model TARGET COLUMN 'col' ALGORITHM 'xgboost'
    /// ^~~~~~~~~~~~~~~definition~~~~~~~~~~~~~~~^
    ASTPtr definition_ast;

    // Model name
    String name;

    // Model's target column in the table
    String target_column;

    // Boosting algorithm, e.g. 'xgboost' or 'lightgbm'
    String algorithm;

    Model() = default;

    static Model getTableModelFromAST(
        const ASTPtr & definition_ast, const ColumnsDescription & columns, ContextPtr context);

    // /// Parse description from string
    // static Model parse(const String & str, const ColumnsDescription & columns, ContextPtr context, const KeyDescription & primary_key, bool is_attach);
};

}
