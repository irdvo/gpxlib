#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include <memory>

#include "doctest.h"

#include "gpx/Algorithm.h"
#include "gpx/Parser.h"
#include "gpx/Writer.h"

class ReportCheck : public gpx::Report
{
public:
  ReportCheck() : _warning(gpx::Report::SUCCESS) {}
  ~ReportCheck() {}

  virtual void report(const gpx::Node *, gpx::Report::Warning warning, const std::string &)
  {
    _warning = warning;
  }

  gpx::Report::Warning warning()
  {
    gpx::Report::Warning temp = _warning;

    _warning = gpx::Report::SUCCESS;

    return temp;
  }

private:
  gpx::Report::Warning _warning;
};


TEST_CASE("gpxlib tests")
{
  const std::string xml =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<gpx>\n"
      " <trk>\n"
      "  <name>Test</name>\n"
      "  <trkseg>\n"
      "   <trkpt lat=\"50.7\" lon=\"6.4\">\n"
      "    <extensions>\n"
      "     <pass_through>True</pass_through>\n"
      "    </extensions>\n"
      "   </trkpt>\n"
      "  </trkseg>\n"
      " </trk>\n"
      "</gpx>\n";

  //
  // Parsing WPT extensions
  //

  ReportCheck report;

  gpx::Parser parser(&report);

  CHECK(parser.parse(xml, true));

  CHECK_EQ(report.warning(), gpx::Report::SUCCESS);

  //
  // GPX pretty printing
  //

  std::stringstream stream;
  gpx::Writer       writer;

  CHECK(writer.write(stream, parser.root(), true));

  CHECK_EQ(stream.str(), xml);

  //
  // Algorithm check
  //

  CHECK_EQ(gpx::distance(50.06639, -5.71472, 58.64389, -3.07000), doctest::Approx(968853.52).epsilon(0.001));

  CHECK_EQ(gpx::bearing (50.06639, -5.71472, 58.64389, -3.07000), doctest::Approx(0.16).epsilon(0.001));

  CHECK_EQ(gpx::crosstrack(53.3206, -1.7297, 53.1887, 0.1334, 53.2611, -0.7972), doctest::Approx(-307.55).epsilon(0.001));
}

TEST_CASE("copy nodes")
{
  const std::string xml =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<gpx>\n"
      " <trk>\n"
      "  <name>Test</name>\n"
      "  <trkseg>\n"
      "   <trkpt lat=\"50.7\" lon=\"6.4\">\n"
      "   </trkpt>\n"
      "  </trkseg>\n"
      " </trk>\n"
      "</gpx>\n";


  ReportCheck report;

  gpx::Parser parser(&report);

  CHECK(parser.parse(xml, true));

  CHECK_EQ(report.warning(), gpx::Report::SUCCESS);

  gpx::GPX *root = parser.root();

  CHECK_NE(root, nullptr);

  std::list<gpx::TRK*> &trks = root->trks().list();

  CHECK(!trks.empty());

  gpx::TRK* trk = *(trks.begin());

  CHECK(trk);

  std::list<gpx::TRKSeg*> trksegs = trk->trksegs().list();

  CHECK(!trksegs.empty());

  gpx::TRKSeg* trkseg = *(trksegs.begin());

  CHECK(trkseg);

  std::list<gpx::WPT*> wpts = trkseg->trkpts().list();

  CHECK(!wpts.empty());

  gpx::WPT* wpt = *(wpts.begin());


  CHECK_EQ(wpt->lat().getValue(), "50.7");
  CHECK_EQ(wpt->lon().getValue(), "6.4");


  std::unique_ptr<gpx::WPT> node(new gpx::WPT(nullptr, "trkpt", gpx::Node::ELEMENT, false));

  CHECK(node);

  node->copy(wpt, &report);

  CHECK_EQ(report.warning(), gpx::Report::SUCCESS);


  CHECK_EQ(node->lat().getValue(), "50.7");
  CHECK_EQ(node->lon().getValue(), "6.4");


  CHECK_EQ(wpt->lat().getValue(), "50.7");
  CHECK_EQ(wpt->lon().getValue(), "6.4");
}
