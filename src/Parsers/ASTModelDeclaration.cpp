#include <Parsers/ASTModelDeclaration.h>
#include <Common/quoteString.h>
#include <IO/Operators.h>


namespace DB
{

String ASTModelDeclaration::getID(char delim) const
{
    return "ModelDeclaration" + (delim + name);
}

ASTPtr ASTModelDeclaration::clone() const
{
    auto res = std::make_shared<ASTModelDeclaration>(*this);
    res->children.clear();

    if (target_column)
    {
        res->target_column = target_column->clone();
        res->children.push_back(res->target_column);
    }

    if (algorithm)
    {
        res->algorithm = algorithm->clone();
        res->children.push_back(res->algorithm);
    }

    return res;
}

void ASTModelDeclaration::formatImpl(WriteBuffer & ostr, const FormatSettings & format_settings, FormatState & state, FormatStateStacked frame) const
{
    frame.need_parens = false;

    format_settings.writeIdentifier(ostr, name, /*ambiguous=*/true);

    if (target_column)
    {
        ostr << ' ';
        target_column->format(ostr, format_settings, state, frame);
    }

    if (algorithm)
    {
        ostr << ' ';
        algorithm->format(ostr, format_settings, state, frame);
    }
}

}
