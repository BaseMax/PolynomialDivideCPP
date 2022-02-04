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

#ifndef POLYNOMIAL_POLYNOMIAL_RESULT_H
#define POLYNOMIAL_POLYNOMIAL_RESULT_H

#include <string>

namespace mathematics
{
template<typename Data>
struct Result
{
	enum class Status
	{
		kSuccess,
		kFailure
	};

	Data data;
	Status status = Status::kFailure;
	std::string message;

	explicit Result(std::string const& message_in,
					Status status_in = Status::kFailure)
		: status(status_in)
		, message(message_in)
	{
	}
	explicit Result(Status status_in = Status::kFailure,
					Data&& data_in = {},
					std::string const& message_in = {})
		: data(std::forward<Data>(data_in))
		, status(status_in)
		, message(message_in)
	{
	}

	operator bool() noexcept
	{
		return status == Status::kSuccess;
	}
	void clear() noexcept
	{
		message.clear();
		status = Status::kSuccess;
	}
};
} // namespace mathematics

#endif // POLYNOMIAL_POLYNOMIAL_RESULT_H
