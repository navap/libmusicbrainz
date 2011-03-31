#include <fstream>
#include <string>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/mbxmlparser.h>
#include <musicbrainz3/metadata.h>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

#include "read_file.h"

class ParseReleaseGroupTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseReleaseGroupTest);
	CPPUNIT_TEST(testReleaseGroupBasic);
	CPPUNIT_TEST(testReleaseGroupSearch);
	CPPUNIT_TEST_SUITE_END();

protected:

	void testReleaseGroupBasic()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/release-group/The_Cure_1.xml"));
		ReleaseGroup *releaseGroup = md->getReleaseGroup();
		CPPUNIT_ASSERT(releaseGroup);
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release-group/c6a62b78-70f7-44f7-b159-064f6b7ba03a"), releaseGroup->getId());
		CPPUNIT_ASSERT_EQUAL(string("The Cure"), releaseGroup->getTitle());
		CPPUNIT_ASSERT_EQUAL(NS_MMD_1 + string("Album"), releaseGroup->getType());
		CPPUNIT_ASSERT_EQUAL(4, releaseGroup->getNumReleases());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release/d984e1a3-7281-46bb-ad8b-1478a00f2fbf"), releaseGroup->getRelease(0)->getId());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release/61a4ec51-fa34-4757-85d7-83231776ed14"), releaseGroup->getRelease(3)->getId());
	}

	void testReleaseGroupSearch()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/release-group/search_result_1.xml"));
		ReleaseGroupResultList r = md->getReleaseGroupResults();
		
		CPPUNIT_ASSERT_EQUAL(3, int(r.size()));
		CPPUNIT_ASSERT_EQUAL(100, r[0]->getScore());
		CPPUNIT_ASSERT_EQUAL(98, r[1]->getScore());
		CPPUNIT_ASSERT_EQUAL(90, r[2]->getScore());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release-group/963eac15-e3da-3a92-aa5c-2ec23bfb6ec2"), r[0]->getReleaseGroup()->getId());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release-group/0bd324a3-1c90-3bdb-8ca4-4101a580c62c"), r[1]->getReleaseGroup()->getId());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/release-group/ea7d8352-7751-30be-8490-bb6df737f47c"), r[2]->getReleaseGroup()->getId());
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseReleaseGroupTest);
