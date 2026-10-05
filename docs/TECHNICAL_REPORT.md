# Project A: Municipal Financial Management System

PAP521S - Programming in Practice

Member names and student numbers are recorded in README.md.

## 1. Introduction

MFMS is a C99 console application that demonstrates foundational programming
through municipal employee, budget, supplier, asset and reporting workflows.
This report describes the integrated repository and shared input validation.
Module owners should confirm their sections before the group submits it.

## 2. Problem description

Municipal information must be organised so users can locate records, calculate
salary costs and identify departments that spend more than their allocations.
Unvalidated input can cause incorrect values, misaligned fields or stalled menus.
The foundation application models these operations using in-memory records.

## 3. System objectives

Provide clear menus; add, display and search records; calculate employee pay and
budget balances; produce four reports; validate input consistently; organise
functions across modules; and manage source versions using Git.

## 4. System features

Employees have an ID, name, department, salary and allowances. Users can search
by name and calculate pay by ID. Budgets contain department names, allocations,
spending, remaining balances and exceeded flags. Duplicate department entries
are rejected. Suppliers store contact and location details. Assets store name,
type, value, department and condition. Reports provide salary statistics, budget
totals and overspent departments, plus supplier and asset listings.

## 5. Program design

The main menu dispatches to module functions. Main owns three record arrays and
counts; budget.c owns shared departmental budgets. Header files define structures
and function declarations. Add functions check capacity, validate a temporary
record and append only after every field succeeds. Loops traverse arrays and
strcmp performs exact-name searches. Reports reuse existing records and display
functions. The system stores a maximum of 100 employees, 20 budgets, 100 suppliers
and 100 assets; all records are lost on exit.

Shared validation is implemented in validation.c and validation.h. Full-line input is trimmed and checked
before conversion. Integer input must be in the requested range; monetary input
must be finite and non-negative. Invalid suffixes, overflow and overlong text are
rejected. Closed input cancels incomplete records and backs out of menus.

## 6. Challenges encountered

Input handling differed across modules. Some code mixed scanf with fgets and
single-character newline removal, allowing trailing input to affect later fields.
Some loops did not stop on EOF. Asset values were not checked, and supplier text
could be blank. Main and reports duplicated their menu parsing.

## 7. Solutions implemented

Shared validation replaces the inconsistent input readers while retaining module
interfaces. Add functions now return on closed input before saving partial data.
Documentation explains source
files, build commands, use, testing and repository coordination.

Twelve automated integration tests compile and execute the full system. They
verify calculations, searches, reports, invalid input, empty data, supplier
capacity and closed-input handling. All passed on Linux with strict C99 compiler
warnings treated as errors. The reproducible runner and output are included.
Windows execution still needs a local demonstration check.

## 8. Conclusion

The integrated application demonstrates arrays, strings, functions, parameters,
loops, decisions and arithmetic. Shared input validation improves consistent
behaviour across modules. Current limits include volatile storage, exact case-sensitive
searches, no contact-format checks and floating-point monetary arithmetic.
Persistent storage and stronger financial rules are possible extensions for
Project B. Member review remains necessary before final submission.
