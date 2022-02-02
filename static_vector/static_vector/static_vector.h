
#pragma once

template <typename VectorType>
class static_vector_iterator
{
public:
	using value_type = typename VectorType::value_type;
	using difference_type = typename VectorType::difference_type;

public:
	explicit constexpr static_vector_iterator() = default;

	explicit constexpr static_vector_iterator(value_type* ptr)
		: m_ptr(ptr)
	{
	}

public: // comparators
	constexpr auto operator<=>(const static_vector_iterator&) const = default;

public: // accessors
	constexpr auto& operator*() const
	{
		return *m_ptr;
	}

public: // modifiers
	constexpr auto& operator++() noexcept
	{
		++m_ptr;
		return *this;
	}

	constexpr auto operator++(int) noexcept
	{
		const auto tmp = *this;
		++(*this);

		return tmp;
	}

	constexpr auto& operator--() noexcept
	{
		--m_ptr;
		return *this;
	}

	constexpr auto operator--(int) noexcept
	{
		const auto tmp = *this;
		--(*this);

		return tmp;
	}

public: // arithmetic operators
	constexpr auto& operator+=(std::size_t increment) noexcept
	{
		m_ptr += increment;
		return *this;
	}

	constexpr auto operator+(std::size_t offset) noexcept
	{
		auto tmp = *this;
		return tmp += offset;
	}

	constexpr auto& operator-=(std::size_t decrement) noexcept
	{
		m_ptr -= decrement;
		return *this;
	}

	constexpr auto operator-(std::size_t offset) noexcept
	{
		auto tmp = *this;
		return tmp -= offset;
	}

	constexpr auto operator-(static_vector_iterator<VectorType> rhs)
	{
		return m_ptr - rhs.m_ptr;
	}

private:
	value_type* m_ptr;
};

template <typename T, std::size_t Capacity>
class static_vector
{
public:
	using iterator = static_vector_iterator<static_vector<T, Capacity>>;
	using value_type = T;
	using difference_type = std::ptrdiff_t;

public:
	explicit constexpr static_vector() = default;

public: // element access
	constexpr auto operator[](std::size_t index)
	{
		return m_data[index];
	}

public: // iterators
	constexpr auto begin() noexcept
	{
		return iterator(m_data);
	}

	constexpr auto end() noexcept
	{
		return iterator(m_data + m_size);
	}

public: // storage
	constexpr auto size() const noexcept
	{
		return m_size;
	}

	constexpr auto capacity() const noexcept
	{
		return Capacity;
	}

public: // modifiers
	constexpr void push_back(T item)
	{
		m_data[m_size++] = item;
	}

	constexpr void pop_back()
	{
		m_data[--m_size].~T();
	}

	constexpr auto insert(iterator it, T item)
	{
		std::copy_backward(it, end(), end() + 1);
		*it = item;

		++m_size;

		return it;
	}

	constexpr auto erase(iterator it)
	{
		std::copy(it + 1, end(), it);

		--m_size;

		return it;
	}

private:
	T m_data[Capacity];
	std::size_t m_size;
};
