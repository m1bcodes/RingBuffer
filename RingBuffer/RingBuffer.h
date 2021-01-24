// MIT License
//
//Copyright(c) 2021 m1bcodes
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//

#pragma once

#include <vector>

template<typename T>
class RingBuffer
{
public:
	RingBuffer(std::size_t capacity)
		: m_buffer(capacity)
	{
		clear();
	}

	size_t capacity() const 
	{ 
		return m_buffer.size();
	}

	void clear()
	{
		m_head = 0;
		m_tail = 0;
	}

	bool empty() const
	{
		return size() == 0;
	}

	bool filled() const
	{
		return size() == capacity();
	}

	size_t size() const
	{
		return m_tail;
	}

	void push_back(const T& value)
	{
		if (!filled()) {
			m_buffer[m_tail] = value;
			m_tail++;
			m_head = m_tail;
		}
		else {
			if (m_head >= capacity())
				m_head = 0;
			m_buffer[m_head] = value;
			m_head = (m_head + 1) % capacity();
		}
	}

	T& operator [](int idx) {
		size_t i = readIndex(idx);
		return m_buffer[i];
	}

	const T& operator [](int idx) const {
		size_t i = readIndex(idx);
		return m_buffer[idx];
	}

private:
	size_t readIndex(int idx) const
	{
		return (m_head + idx) % m_tail;
	}

	std::vector<T> m_buffer;
	size_t m_head;
	size_t m_tail;
};
