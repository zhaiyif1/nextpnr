/*
 *  nextpnr -- Next Generation Place and Route
 *
 *  Copyright (C) 2018  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "nextpnr.h"

NEXTPNR_NAMESPACE_BEGIN

Context *IdString::global_ctx = nullptr;

void IdString::set(Context *ctx, const std::string &s)
{
    auto it = ctx->idstring_str_to_idx->find(s);
    if (it == ctx->idstring_str_to_idx->end()) {
        index = ctx->idstring_idx_to_str->size();
        auto insert_rc = ctx->idstring_str_to_idx->insert({s, index});
        ctx->idstring_idx_to_str->push_back(&insert_rc.first->first);
    } else {
        index = it->second;
    }
}

const std::string &IdString::str(Context *ctx) const
{
    return *ctx->idstring_idx_to_str->at(index);
}

const char *IdString::c_str(Context *ctx) const
{
    return str(ctx).c_str();
}

void IdString::initialize_add(Context *ctx, const char *s, int idx)
{
    assert(ctx->idstring_str_to_idx->count(s) == 0);
    assert(int(ctx->idstring_idx_to_str->size()) == idx);
    auto insert_rc = ctx->idstring_str_to_idx->insert({s, idx});
    ctx->idstring_idx_to_str->push_back(&insert_rc.first->first);
}

NEXTPNR_NAMESPACE_END
