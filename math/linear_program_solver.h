/*
Copyright (C) 2017  Liangliang Nan
http://web.siat.ac.cn/~liangliang/ - liangliang.nan@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef _MATH_LINEAR_PROGRAM_SOLVER_H_
#define _MATH_LINEAR_PROGRAM_SOLVER_H_

#include "math_common.h"
#include "linear_program.h"

#include <vector>

#define HAS_SCIP_SOLVER
//#define HAS_GUROBI_SOLVER
//#define HAS_CBC_SOLVER

class MATH_API LinearProgramSolver
{
public:
	enum SolverName { 
#ifdef HAS_GUROBI_SOLVER
		GUROBI, 
#endif
#ifdef HAS_CBC_SOLVER
		CBC,
#endif
#ifdef HAS_SCIP_SOLVER
		SCIP, 
#endif
		GLPK, 
		LPSOLVE
	};

	typedef LinearProgram<double>	LinearProgram;

public:
	LinearProgramSolver() {}
	~LinearProgramSolver() {}

	// Solves the problem and returns false if fails.
	// NOTE: Gurobi solver recommended.
	//		 The SCIP solver is slower than Gurobi but acceptable. 
	//       GLPK and LPSOLVE may be too slow or even fail for large problems.
    bool solve(const LinearProgram* program, SolverName solver);

	// returns the objective value
	// NOTE: result is valid only if the solver succeeded
	double get_objective_value() const { return objective_value_; }

	// returns the result
	// NOTE: (1) result is valid only if the solver succeeds
	//       (2) the result includes all auxiliary variables
	//       (3) for integer variables, you need to round the values
	const std::vector<double>& get_result() const { return result_; }

private:
#ifdef HAS_GUROBI_SOLVER
	bool _solve_GUROBI(const LinearProgram* program);
#endif
#ifdef HAS_CBC_SOLVER
	bool _solve_CBC(const LinearProgram* program);
#endif
	bool _solve_SCIP(const LinearProgram* program);
	bool _solve_GLPK(const LinearProgram* program);
	bool _solve_LPSOLVE(const LinearProgram* program);

private:
	std::vector<double> result_;
	double				objective_value_;
};

#endif
