#include "baseview.hpp"
#include <gtkmm.hpp>
#include <string>


/**
 * Constructor
 * 
 * @param title
 * @param page
*/
BaseView::BaseView(std::string const &title, unsigned int page)
    : _title(title), _identifier(page)
{
}


/**
 * Method to set the title of the view
 * 
 * @param title
*/
void BaseView::setTitle(std::string const &title)
{
    this->_title = title;
}


/**
 * Method to set the identifier of the view
 * 
 * @param page
*/
void BaseView::setIdentifier(unsigned int page)
{
    this->_identifier = page;
}


/**
 * Method to get the title of the page
 * 
 * @return std::string
*/
std::string BaseView::getTitle()
{
    return this->_title;
}


/**
 * Method to get the indentifier of the page
 * 
 * @return unsigned int
*/
unsigned int BaseView::getIdentifier()
{
    return this->_identifier;
}