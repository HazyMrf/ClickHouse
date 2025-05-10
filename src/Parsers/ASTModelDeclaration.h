#pragma once

#include <Parsers/IAST.h>

namespace DB
{

/** Name, target column, algorithm, model settings
 */
class ASTModelDeclaration : public IAST
{
public:
    String name;
    ASTPtr target_column;
    ASTPtr algorithm;

    String getID(char) const override;

    ASTPtr clone() const override;

protected:
    void formatImpl(WriteBuffer & ostr, const FormatSettings & format_settings, FormatState & state, FormatStateStacked frame) const override;
};

}
