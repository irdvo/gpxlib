#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "gpx/Parser.h"

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


TEST_CASE("Parsing WPT extensions")
{
  const std::string xml =
      "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<gpx>"
      "<trk>"
      "  <name>Test</name>"
      "  <trkseg>"
      "    <trkpt lat=\"50.7\" lon=\"6.4\">"
      "      <extensions>"
      "        <pass_through>True</pass_through>"
      "      </extensions>"
      "    </trkpt>"
      "  </trkseg>"
      "</trk>"
      "</gpx>";

  ReportCheck report;

  gpx::Parser parser(&report);

  CHECK(parser.parse(xml, true));
  CHECK((report.warning() == gpx::Report::SUCCESS));
}
