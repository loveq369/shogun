#include <shogun/lib/config.h>
#include <shogun/mathematics/Random.h>
#include <shogun/mathematics/Math.h>
#include <shogun/lib/SGVector.h>
#include <gtest/gtest.h>

using namespace shogun;

/**
 * NOTE: these unit tests were generated with MEXP=19937
 * with other exponents it is expected to fail!
 */

TEST(Random, uint32_t)
{
	CRandom* prng = new CRandom();
	uint32_t r = prng->random_32();
	SG_UNREF(prng);
	EXPECT_EQ(1811630862U, r);
}

TEST(Random, uint64_t)
{
	CRandom* prng = new CRandom();
	uint64_t r = prng->random_64();
	SG_UNREF(prng);
	EXPECT_EQ(18328733385137801998U, r);
}

TEST(Random, fill_array_uint32)
{
	CRandom* prng = new CRandom();
	uint32_t t = 2228230814U;
	SGVector<uint32_t> rv(2*SFMT_N32+1);
	prng->fill_array(rv.vector, rv.vlen);
	
	EXPECT_EQ(t, rv[SFMT_N32]);
}

#ifdef HAVE_SSE2
TEST(Random, fill_array_uint32_simd)
{
	CRandom* prng = new CRandom();
	uint32_t t = 2228230814U;
	SGVector<uint32_t> rv(2*SFMT_N32);
	prng->fill_array(rv.vector, rv.vlen);
	SG_UNREF(prng);

	EXPECT_EQ(t, rv[SFMT_N32]);
}
#endif

TEST(Random, fill_array_uint64)
{
	CRandom* prng = new CRandom();
	uint64_t t = 9564086722318310046U;
	SGVector<uint64_t> rv(2*SFMT_N64+1);
	prng->fill_array(rv.vector, rv.vlen);
	SG_UNREF(prng);

	EXPECT_EQ(t, rv[SFMT_N64]);
}

#ifdef HAVE_SSE2
TEST(Random, fill_array_uint64_simd)
{
	CRandom* prng = new CRandom();
	uint64_t t = 9564086722318310046U;
	SGVector<uint64_t> rv(2*SFMT_N64);
	prng->fill_array(rv.vector, rv.vlen);
	SG_UNREF(prng);

	EXPECT_EQ(t, rv[SFMT_N64]);
}
#endif

TEST(Random, fill_array_oc)
{
	CRandom* prng = new CRandom();
	float64_t t = 0.25551924513287405;
	SGVector<float64_t> rv(2*dsfmt_get_min_array_size()+1);
	prng->fill_array_oc(rv.vector, rv.vlen);
	SG_UNREF(prng);

	EXPECT_DOUBLE_EQ(t, rv[dsfmt_get_min_array_size()]);
}

#ifdef HAVE_SSE2
TEST(Random, fill_array_oc_simd)
{
	CRandom* prng = new CRandom();
	float64_t t = 0.25551924513287405;
	SGVector<float64_t> rv(2*dsfmt_get_min_array_size());
	prng->fill_array_oc(rv.vector, rv.vlen);
	SG_UNREF(prng);

	EXPECT_DOUBLE_EQ(t, rv[dsfmt_get_min_array_size()]);
}
#endif

TEST(Random, normal_distrib)
{
	CRandom* prng = new CRandom();
	float64_t t = 75.567130769021162;
	float64_t r = prng->normal_distrib(100.0, 10.0);
	SG_UNREF(prng);

	EXPECT_DOUBLE_EQ(t, r);
}

TEST(Random, random_uint64_1_2)
{
	CMath::init_random(17);
	for (int32_t i=0; i<10000; i++)
	{
		uint64_t r=CMath::random((uint64_t) 1, (uint64_t) 2);
		EXPECT_TRUE(r == 1 || r == 2);
	}
}

TEST(Random, random_uint64_0_10)
{
	CMath::init_random(17);
	int rnds[10] = {0,0,0,0,0,0};
	for (int32_t i=0; i<10000; i++)
	{
		uint64_t r=CMath::random((uint64_t) 0, (uint64_t) 9);
		rnds[r]++;
	}

	for (int32_t i=0; i<10; i++) {
		EXPECT_TRUE(rnds[i]>0);
	}
}

TEST(Random, random_int64_1_2)
{
	CMath::init_random(17);
	for (int32_t i=0; i<10000; i++)
	{
		int64_t r=CMath::random((int64_t) 1, (int64_t) 2);
		EXPECT_TRUE(r == 1 || r == 2);
	}
}

TEST(Random, random_int64_0_10)
{
	CMath::init_random(17);
	int rnds[10] = {0,0,0,0,0,0};
	for (int32_t i=0; i<10000; i++)
	{
		int64_t r=CMath::random((int64_t) 0, (int64_t) 9);
		rnds[r]++;
	}

	for (int32_t i=0; i<10; i++) {
		EXPECT_TRUE(rnds[i]>0);
	}
}

TEST(Random, random_uint32_1_2)
{
	CMath::init_random(17);
	for (int32_t i=0; i<10000; i++)
	{
		uint32_t r=CMath::random((uint32_t) 1, (uint32_t) 2);
		EXPECT_TRUE(r == 1 || r == 2);
	}
}

TEST(Random, random_uint32_0_10)
{
	CMath::init_random(17);
	int rnds[10] = {0,0,0,0,0,0};
	for (int32_t i=0; i<10000; i++)
	{
		uint32_t r=CMath::random((uint32_t) 0, (uint32_t) 9);
		rnds[r]++;
	}

	for (int32_t i=0; i<10; i++) {
		EXPECT_TRUE(rnds[i]>0);
	}
}

TEST(Random, random_int32_1_2)
{
	CMath::init_random(17);
	for (int32_t i=0; i<10000; i++)
	{
		int32_t r=CMath::random((int32_t) 1, (int32_t) 2);
		EXPECT_TRUE(r == 1 || r == 2);
	}
}

TEST(Random, random_int32_0_10)
{
	CMath::init_random(17);
	int rnds[10] = {0,0,0,0,0,0};
	for (int32_t i=0; i<10000; i++)
	{
		int32_t r=CMath::random((int32_t) 0, (int32_t) 9);
		rnds[r]++;
	}

	for (int32_t i=0; i<10; i++) {
		EXPECT_TRUE(rnds[i]>0);
	}
}