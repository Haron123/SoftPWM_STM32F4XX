#include "gpio_helper.h"

void gpio_setup_basic(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode)
{
    // Error Handling
    if(port == NULL)
    {
        // Error
        // Invalid port
        ERROR_HANDLER("Invalid GPIO_TypeDef Port");
    }
    else if(pin > 15)
    {
        // Error
        ERROR_HANDLER("Invalid Pin, each Port only has PIN0-PIN15");
    }
    else if(port_mode > ANALOG)
    {
        // Error
        ERROR_HANDLER("Selected Port Mode doesnt exist");
    }
    else
    {
        // Clear the Moder Bits before setting them
        port->MODER &= ~(3 << (pin * 2));
        port->MODER |= (port_mode << (pin * 2));
        
        // Clear the Purpdr Bits before setting them
        port->PUPDR &= ~(3 << (pin * 2));
        //port->PUPDR |= (NO_PULL << (pin * 2) Happens implicit due writing a zero

        // Clear the OTYPER bits before setting them
        port->OTYPER &= ~(1 << pin);
        //port->OTYPER |= (PUSH_PULL << pin); Happens implicit due writing a zero

        // Clear the OTYPER bits before setting them
        port->OSPEEDR &= ~(3 << (pin * 2));
        //port->OSPEEDR |= (LOW_SPEED << pin); Happens implicit due writing a zero
    }
}

void gpio_setup_normal(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode, uint8_t pull_type)
{
    // Error Handling
    if(port == NULL)
    {
        // Error
        // Invalid port
        ERROR_HANDLER("Invalid GPIO_TypeDef Port");
    }
    else if(pin > 15)
    {
        // Error
        ERROR_HANDLER("Invalid Pin, each Port only has PIN0-PIN15");
    }
    else if(port_mode > ANALOG)
    {
        // Error
        ERROR_HANDLER("Selected Port Mode doesnt exist");
    }
    else if(pull_type >= RESERVED)
    {
        if(pull_type == RESERVED)
        {
            ERROR_HANDLER("Selected Pull Type is reserved");
        }
        else
        {
            ERROR_HANDLER("Selected Pull Type doesnt exist");
        }
    }
    else
    {
        // Clear the Moder Bits before setting them
        port->MODER &= ~(3 << (pin * 2));
        port->MODER |= (port_mode << (pin * 2));
        
        // Clear the Purpdr Bits before setting them
        port->PUPDR &= ~(3 << (pin * 2));
        port->PUPDR |= (pull_type << (pin * 2));

        // Clear the OTYPER bits before setting them
        port->OTYPER &= ~(1 << pin);
        //port->OTYPER |= (PUSH_PULL << pin); Happens implicit due writing a zero

        // Clear the OTYPER bits before setting them
        port->OSPEEDR &= ~(3 << (pin * 2));
        //port->OSPEEDR |= (LOW_SPEED << pin); Happens implicit due writing a zero
    }    
}

void gpio_setup_full(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode, uint8_t pull_type, uint8_t output_type, uint8_t speed)
{
    // Error Handling
    if(port == NULL)
    {
        // Error
        // Invalid port
        ERROR_HANDLER("Invalid GPIO_TypeDef Port");
    }
    else if(pin > 15)
    {
        // Error
        ERROR_HANDLER("Invalid Pin, each Port only has PIN0-PIN15");
    }
    else if(port_mode > ANALOG)
    {
        // Error
        ERROR_HANDLER("Selected Port Mode doesnt exist");
    }
    else if(pull_type >= RESERVED)
    {
        if(pull_type == RESERVED)
        {
            ERROR_HANDLER("Selected Pull Type is reserved");
        }
        else
        {
            ERROR_HANDLER("Selected Pull Type doesnt exist");
        }
    }
    else if(output_type > OPEN_DRAIN)
    {
        ERROR_HANDLER("Selected Output Type doesnt exist");
    }
    else if(output_type > VERY_HIGH_SPEED)
    {
        ERROR_HANDLER("Theres no Super very high speed bro");
    }
    else
    {
        // Clear the Moder Bits before setting them
        port->MODER &= ~(3 << (pin * 2));
        port->MODER |= (port_mode << (pin * 2));
        
        // Clear the Purpdr Bits before setting them
        port->PUPDR &= ~(3 << (pin * 2));
        port->PUPDR |= (pull_type << (pin * 2));

        // Clear the OTYPER bits before setting them
        port->OTYPER &= ~(1 << pin);
        port->OTYPER |= (output_type << pin);

        // Clear the OTYPER bits before setting them
        port->OSPEEDR &= ~(3 << (pin * 2));
        port->OSPEEDR |= (speed << (pin * 2));
    }
}