/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * @another_ghasem
 * g1999ramezani@gmail.com
 */

#include "Polynomial/Polynomial.h"

#include <iostream>

int main()
{
	mathematics::Polynomial poly1;
	mathematics::Polynomial poly2;

	using Expr = mathematics::Polynomial::Expression;
	poly1 << Expr(5.0, 2) << Expr(4.0, 1) << Expr(2.0, 0);
	poly2 << Expr(5.0, 1) << Expr(5.0, 0);

	auto const devide_result = poly1 / poly2;
	std::cout << "Quotient: " << devide_result.data.first << std::endl;
	std::cout << "Remainder: " << devide_result.data.second << std::endl;
}
