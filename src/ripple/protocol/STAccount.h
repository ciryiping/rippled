//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_PROTOCOL_STACCOUNT_H_INCLUDED
#define RIPPLE_PROTOCOL_STACCOUNT_H_INCLUDED

#include <ripple/protocol/RippleAddress.h>
#include <ripple/protocol/STBlob.h>
#include <string>

namespace ripple {

class STAccount final
    : public STBlob
{
public:
    STAccount (SField::ref n, Buffer&& v)
            : STBlob (n, std::move(v))
    {
        ;
    }
    STAccount (SField::ref n, Account const& v);
    STAccount (SField::ref n) : STBlob (n)
    {
        ;
    }
    STAccount ()
    {
        ;
    }
    static std::unique_ptr<STBase> deserialize (SerialIter& sit, SField::ref name)
    {
        return std::unique_ptr<STBase> (construct (sit, name));
    }

    SerializedTypeID getSType () const override
    {
        return STI_ACCOUNT;
    }
    std::string getText () const override;

    RippleAddress getValueNCA () const;
    void setValueNCA (RippleAddress const& nca);

    template <typename Tag>
    void setValueH160 (base_uint<160, Tag> const& v)
    {
        peekValue () = Buffer (v.data (), v.size ());
        assert (peekValue ().size () == (160 / 8));
    }

    template <typename Tag>
    bool getValueH160 (base_uint<160, Tag>& v) const
    {
        auto success = isValueH160 ();
        if (success)
            memcpy (v.begin (), peekValue ().data (), (160 / 8));
        return success;
    }

    bool isValueH160 () const;

    std::unique_ptr<STBase>
    duplicate () const override
    {
        return std::make_unique<STAccount>(*this);
    }

private:
    static STAccount* construct (SerialIter&, SField::ref);
};

} // ripple

#endif
