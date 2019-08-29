/*
 * Button.h
 *
 *  Created on: Aug 29, 2019
 *      Author: sergey
 */

#ifndef MODEL_BUTTON_H_
#define MODEL_BUTTON_H_

#include "stm32f407xx.h"
#include "tm_stm32_button.h"

namespace Model {

class Button {
private:
	GPIO_TypeDef _GPIO_Type;
	unsigned short int _GPIO_Pin;
public:
	Button(GPIO_TypeDef *type, unsigned short int pin);
	virtual ~Button();
};

} /* namespace Model */

#endif /* MODEL_BUTTON_H_ */
