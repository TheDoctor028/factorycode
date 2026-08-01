#pragma once

// Declare the imported function from the host engine
extern "C" __attribute__((import_module("env"), import_name("hello")))
void hello();

// Define an inline export function so it can live in the header safely
extern "C" __attribute__((export_name("run"), visibility("default"))) 
void run();
