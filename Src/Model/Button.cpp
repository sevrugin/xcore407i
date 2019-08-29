/*
 * Button.cpp
 *
 *  Created on: Aug 29, 2019
 *      Author: sergey
 */

#include "Button.h"

namespace Model {

Button::Button(GPIO_TypeDef *type, unsigned short int pin) {
	_GPIO_Type = *type;
	_GPIO_Pin = pin;

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

} /* namespace Model */
