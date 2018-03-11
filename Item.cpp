//
// Item.cpp
// Copyright (c) Charles Baker. All rights reserved.
//    

#include "Item.hpp"
#include "Symbol.hpp"
#include "Production.hpp"
#include "assert.hpp"

using std::vector;
using namespace sweet;
using namespace sweet::lalr;

/**
// Constructor.
*/
Item::Item()
: production_(),
  position_( 0 ),
  lookahead_symbols_()
{
}

/**
// Constructor.
//
// @param production
//  The production that this item is for.
//
// @param position
//  The position of the dot in this item.
*/
Item::Item( Production* production, int position )
: production_( production ),
  position_( position ),
  lookahead_symbols_()
{
    SWEET_ASSERT( production_ );
    SWEET_ASSERT( position_ >= 0 && position_ < production_->length() + 1 );
}

/**
// Get the production for this item.
*/
Production* Item::production() const
{
    return production_;
}

/**
// Get the position of the dot in this item.
//
// @return
//  The position of the dot in this item.
*/
int Item::position() const
{
    return position_;
}

/**
// Is the dot that marks the position of this item at the beginning of the
// production?
//
// @return
//  True if the dot is at the beginning of the production otherwise false.
*/
bool Item::dot_at_beginning() const
{
    return position_ == 0;
}

/**
// Is the dot that marks the position of this item at the end of the 
// production?
//
// @return
//  True if the dot is at the end of the production otherwise false.
*/
bool Item::dot_at_end() const
{
    return position_ == production_->length();
}

/**
// Is \e symbol one of the symbols that could be visited next from this item?
//
// @param symbol
//  The symbol to check for being a next symbol of this item.
//
// @return
//  True if \e symbol could be one of the next symbols to be visited from
//  this item otherwise false.
*/
bool Item::next_node( const Symbol& symbol ) const
{
    return production_->symbol_by_position(position_) == &symbol;
}

/**
// Get the lookahead set for this item.
//
// @return
//  The lookahead set.
*/
const std::set<const Symbol*>& Item::lookahead_symbols() const
{
    return lookahead_symbols_;
}

/**
// Less than operator.
//
// @param item
//  The item to compare this item with.
//
// @return 
//  True if this items production is less than \e item's or if this item's
//  production is the same as \e item's then if this item's next nodes
//  are lexically less than item's otherwise false.
*/
bool Item::operator<( const Item& item ) const
{
    return 
        production_->index() < item.production_->index() || 
        (production_->index() == item.production_->index() && position_ < item.position_)
    ;
}

/**
// Add \e lookahead_symbols to the lookahead symbols for this item.
//
// @param lookahead_symbols
//  The lookahead symbols to add to this item.
//
// @return
//  The number of symbols added to the lookahead set of this item.
*/
int Item::add_lookahead_symbols( const std::set<const Symbol*>& lookahead_symbols ) const
{
    size_t original_size = lookahead_symbols_.size();
    lookahead_symbols_.insert( lookahead_symbols.begin(), lookahead_symbols.end() );
    return lookahead_symbols_.size() - original_size;
}
