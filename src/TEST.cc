#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>

#include "TEST.h"
#include "util.h"
#include "Event.h"
#include "file_analysis/Manager.h"

#include "events.bif.h"

using namespace std;
using namespace file_analysis;

void print_bytes(std::ostream& out, const char *title, const unsigned char *data, size_t dataLen, bool format = true) {
    out << title << std::endl;
    out << std::setfill('0');
    for(size_t i = 0; i < dataLen; ++i) {
        out << std::hex << std::setw(2) << (int)data[i];
        if (format) {
            out << (((i + 1) % 16 == 0) ? "\n" : " ");
        }
    }
    out << std::endl;
}

TEST::TEST(RecordVal* args, File* file)
    : file_analysis::Analyzer(file_mgr->GetComponentTag("TEST"), args, file)
{
	fed = false;
	total_len = 0;
}

TEST::~TEST()
{
	total_len = 0;
	
	if ( bufv.size() > 0 ) {
		bufv.clear();
	}
}

file_analysis::Analyzer* TEST::Instantiate(RecordVal* args, File* file)
{
	return new TEST(args, file);
}

bool TEST::DeliverStream(const u_char* data, uint64 len)
{
	if ( ! fed ) {
		fed = len > 0;
	}

	if ( total_len < TEST_MAX_BUFFER) {
		bufv.insert(bufv.end(), data, data+len);
		total_len += len;
	}

	return true;
}

bool TEST::EndOfFile()
{
	Finalize();
	return false;
}

bool TEST::Undelivered(uint64 offset, uint64 len)
{
	return false;
}

void TEST::Finalize()
{
	if ( ! fed ) {
		return;
	}

	std::cout << "TEST::Finalize total_len = " << total_len << std::endl;
	print_bytes(std::cout, "BUFFER", (const u_char *)&bufv[0], total_len);

	val_list* vl = new val_list();
	vl->append(GetFile()->GetVal()->Ref());

	mgr.QueueEvent(file_test, vl);
}
