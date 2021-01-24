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
 
#include "pch.h"
#include "RingBuffer.h"

TEST(RingBufferTest, capacity) {
	RingBuffer<int> r(10);
	EXPECT_EQ(r.capacity(), 10);
}

TEST(RingBufferTest, Insert) {
	const int capa = 10;
	RingBuffer<int> r(capa);
	EXPECT_TRUE(r.empty());
	for (int i = 0; i < 20; i++)
	{
		EXPECT_EQ(r.size(), std::min(i, capa));
		r.push_back(i);
		EXPECT_EQ(r.size(), std::min(i+1, capa));
		EXPECT_FALSE(r.empty());
	}
	r.clear();
	EXPECT_EQ(r.size(), 0);
	EXPECT_TRUE(r.empty());
	EXPECT_TRUE(false);
}

TEST(RingBufferTest, Read) {
	const int capa = 10;
	RingBuffer<int> r(capa);
	std::vector<int> mem;
	for (int i = 0; i < 15; i++)
	{
		r.push_back(i);
		mem.push_back(i);
		EXPECT_EQ(r.size(), std::min(i + 1, capa));
		for (int j = 0; j < r.size(); j++)
		{
			int value = r[j];
			std::cout << value << " ";
			EXPECT_EQ(value, mem[mem.size() - r.size() + j]) << "i=" << i << ", j=" << j;
		}
		std::cout << "\n";
	}
}
