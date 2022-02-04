/*
 *
 *  Copyright 2021 by the contributors <https://github.com/BaseMax/PolynomialAlgorithm/contributors>
 *
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
 */

#ifndef POLYNOMIAL_POLYNOMIAL_POLYNOMIAL_H
#define POLYNOMIAL_POLYNOMIAL_POLYNOMIAL_H

#include "Polynomial/Result.h"

#include <iostream>
#include <optional>
#include <vector>

namespace mathematics
{
class Polynomial
{
public:
	struct Expression final
	{
		using List = std::vector<Expression>;

		float coeff;
		int pow;

		constexpr Expression(float const coeff_in = 0.0,
							 int const pow_in = 0) noexcept
			: coeff(coeff_in)
			, pow(pow_in)
		{
		}
	};

	void addExpression(Expression const& expre)
	{
		exprs_.push_back(expre);
	}
	void addExpression(Expression&& expre)
	{
		exprs_.emplace_back(expre);
	}
	Polynomial& operator<<(Expression const& expre)
	{
		addExpression(expre);
		return *this;
	}
	Polynomial& operator<<(Expression&& epxre)
	{
		addExpression(std::forward<decltype(epxre)>(epxre));
		return *this;
	}
	auto begin()
	{
		return exprs_.begin();
	}
	auto end()
	{
		return exprs_.end();
	}
	auto begin() const
	{
		return exprs_.begin();
	}
	auto end() const
	{
		return exprs_.end();
	}

	Result<Expression*> lastExpression()
	{
		Result<Expression*> result;

		if(exprs_.empty())
		{
			result.message = "We don't have any Expressions.";
			*this << Expression();
		}
		result.data = &exprs_.back();

		return result;
	}

	Result<bool> storeQuotient(float const mul_c, int const diff)
	{
		Result<bool> result("We don't have any expressions");

		if(!exprs_.empty())
		{
			auto& last = exprs_.back();
			last.pow = diff;
			last.coeff = mul_c;

			result.clear();
		}

		return result;
	}

	Result<bool> formNewPoly(int const diff, float const mul_c)
	{
		Result<bool> result("We don't have any expressions");

		if(!exprs_.empty())
		{
			for(auto& expression : exprs_)
			{
				expression.pow += diff;
				expression.coeff *= mul_c;
			}

			result.clear();
		}

		return result;
	}

	Result<Polynomial> sub(Polynomial const& other)
	{
		Result<Polynomial> result;

		if(!exprs_.empty() && !other.exprs_.empty())
		{
			Polynomial poly_res;

			std::size_t poly1_index = 0;
			std::size_t poly2_index = 0;
			for(; poly1_index < exprs_.size() && poly2_index < other.exprs_.size();)
			{
				auto const& poly1 = exprs_[poly1_index];
				auto const& poly2 = other.exprs_[poly2_index];

				if(poly1.pow > poly2.pow)
				{
					poly_res << Expression(poly1.coeff, poly1.pow);
					poly1_index += 1;
				}
				else if(poly1.pow < poly2.pow)
				{
					poly_res << Expression(-1 * poly2.coeff, poly2.pow);
					poly2_index += 1;
				}
				else
				{
					auto const coeff_diff = poly1.coeff - poly2.coeff;
					if(coeff_diff != 0)
					{
						poly_res << Expression(coeff_diff, poly1.pow);
					}
					poly1_index += 1;
					poly2_index += 1;
				}
			}
			for(; poly1_index < exprs_.size() || poly2_index < other.exprs_.size();)
			{
				if(poly1_index < exprs_.size())
				{
					poly_res << exprs_[poly1_index];
					poly1_index += 1;
				}
				if(poly2_index < other.exprs_.size())
				{
					poly_res << other.exprs_[poly2_index];
					poly2_index += 1;
				}
			}

			result.data = poly_res;
		}
		else
		{
			auto constexpr kWeMessage = "We don't have any expressions. ";
			auto constexpr kOtherMessage = "Other doesn't have any expressions.";
			result.message += exprs_.empty() ? kWeMessage : " ";
			result.message += other.exprs_.empty() ? kOtherMessage : " ";
		}

		return result;
	}
	Polynomial operator-(Polynomial const& other) const
	{
		Polynomial result = *this;
		return result.sub(other).data;
	}

	using DevideResult = Result<std::pair<Polynomial, Polynomial>>;
	DevideResult devide(Polynomial const& other)
	{
		DevideResult result;

		if(!exprs_.empty() && !other.exprs_.empty())
		{
			Polynomial quo;
			quo << Expression();

			Polynomial q = *this;
			Polynomial r = other;

			std::size_t poly2_index = 0;

			for(std::size_t index = 0; index < q.exprs_.size(); ++index)
			{
				auto const& q_expr = q.exprs_[index];
				auto const& poly2 = other.exprs_[poly2_index];

				if(q_expr.pow >= poly2.pow)
				{
					auto const diff = q_expr.pow - poly2.pow;
					auto const mul_c = q_expr.coeff / poly2.coeff;
					quo << Expression();
					quo.storeQuotient(mul_c, diff);

					Polynomial q2 = r;
					q2.formNewPoly(diff, mul_c);

					q = q - q2;
					index = -1ULL;
				}
				else
				{
					break;
				}
			}

			result.data.first = quo;
			result.data.second = q;
		}
		else
		{
			auto constexpr kWeMessage = "We don't have any expressions. ";
			auto constexpr kOtherMessage = "Other doesn't have any expressions.";
			result.message += exprs_.empty() ? kWeMessage : " ";
			result.message += other.exprs_.empty() ? kOtherMessage : " ";
		}

		return result;
	}
	DevideResult operator/(Polynomial const& other) const
	{
		return Polynomial(*this).devide(other);
	}

	void show(std::ostream& out = std::cout) const
	{
		std::size_t counter = 0;
		for(std::size_t index = 0; index < exprs_.size(); ++index)
		{
			auto const& expr = exprs_[index];

			if(expr.coeff != 0.0)
			{
				if(counter == 0)
				{
					out << expr.coeff;
				}
				else
				{
					out << (expr.coeff > 0 ? expr.coeff : -expr.coeff);
				}
				counter += 1;

				if(expr.pow != 0)
				{
					out << "x^" << expr.pow;
				}

				if((index + 1) < exprs_.size())
				{
					out << (exprs_[index + 1].coeff > 0 ? " + " : " - ");
				}
			}
		}
	}

private:
	Expression::List exprs_;
};
} // namespace mathematics

std::ostream& operator<<(std::ostream& out, mathematics::Polynomial const& in)
{
	in.show(out);
	return out;
}

#endif // POLYNOMIAL_POLYNOMIAL_POLYNOMIAL_H
