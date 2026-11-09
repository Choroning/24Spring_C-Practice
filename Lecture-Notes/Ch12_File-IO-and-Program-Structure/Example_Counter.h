/**
 * @file    Example_Counter.h
 * @brief   Interface of the counter module: one global variable declaration and three function prototypes
 * @author  박철원 (Cheolwon Park)
 * @date    2026-11-09
 */

#ifndef COUNTER_H
#define COUNTER_H

extern int counter_step;    // Declaration only: the definition is in Example_Counter.c

void counter_reset(void);
void counter_increment(void);
int counter_value(void);

#endif // COUNTER_H
