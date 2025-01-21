#pragma once

void set_variable_value(const char* name, const char* value, int num_bytes);

void set_variable_variable(const char* name, const char* name2);

void add_const_to_var(const char* name, const char* val, int num_bytes);

void add_var_to_var(const char* name, const char* name2);

void add_const_to_var_regs(const char* name, const char* val, int num_bytes);

void add_var_to_var_regs(const char* name, const char* name2);