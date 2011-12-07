
#include <iostream>
#include <vector>
#include "Instance.h"
#include "ShippingException.h"
#include "ActivityImpl.h"

using namespace std;
using Shipping::Exception;

void funnel( )
{
	try {
	    Ptr<Instance::Manager> manager = shippingInstanceManager();
		vector< Ptr<Instance> > source;
		vector< Ptr<Instance> > loc;
		vector< Ptr<Instance> > seg;

		// 10 sets of 10 sources
		source.push_back( manager->instanceNew("customerA1", "Customer") );
		source.push_back( manager->instanceNew("customerA2", "Customer") );
		source.push_back( manager->instanceNew("customerA3", "Customer") );
		source.push_back( manager->instanceNew("customerA4", "Customer") );
		source.push_back( manager->instanceNew("customerA5", "Customer") );
		source.push_back( manager->instanceNew("customerA6", "Customer") );
		source.push_back( manager->instanceNew("customerA7", "Customer") );
		source.push_back( manager->instanceNew("customerA8", "Customer") );
		source.push_back( manager->instanceNew("customerA9", "Customer") );
		source.push_back( manager->instanceNew("customerA10", "Customer") );
		loc.push_back( manager->instanceNew("ttA1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsA1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsA20", "Truck segment") );

		seg[0]->attributeIs("source", "customerA1");
		seg[1]->attributeIs("source", "ttA1");
		seg[1]->attributeIs("return segment", "tsA1");

		seg[2]->attributeIs("source", "customerA2");
		seg[3]->attributeIs("source", "ttA1");
		seg[3]->attributeIs("return segment", "tsA3");

		seg[4]->attributeIs("source", "customerA3");
		seg[5]->attributeIs("source", "ttA1");
		seg[5]->attributeIs("return segment", "tsA5");

		seg[6]->attributeIs("source", "customerA4");
		seg[7]->attributeIs("source", "ttA1");
		seg[7]->attributeIs("return segment", "tsA7");

		seg[8]->attributeIs("source", "customerA5");
		seg[9]->attributeIs("source", "ttA1");
		seg[9]->attributeIs("return segment", "tsA9");

		seg[10]->attributeIs("source", "customerA6");
		seg[11]->attributeIs("source", "ttA1");
		seg[11]->attributeIs("return segment", "tsA11");

		seg[12]->attributeIs("source", "customerA7");
		seg[13]->attributeIs("source", "ttA1");
		seg[13]->attributeIs("return segment", "tsA13");

		seg[14]->attributeIs("source", "customerA8");
		seg[15]->attributeIs("source", "ttA1");
		seg[15]->attributeIs("return segment", "tsA15");

		seg[16]->attributeIs("source", "customerA9");
		seg[17]->attributeIs("source", "ttA1");
		seg[17]->attributeIs("return segment", "tsA17");

		seg[18]->attributeIs("source", "customerA10");
		seg[19]->attributeIs("source", "ttA1");
		seg[19]->attributeIs("return segment", "tsA19");

		loc.push_back( manager->instanceNew("customerB1", "Customer") );
		source.push_back( manager->instanceNew("customerB2", "Customer") );
		source.push_back( manager->instanceNew("customerB3", "Customer") );
		source.push_back( manager->instanceNew("customerB4", "Customer") );
		source.push_back( manager->instanceNew("customerB5", "Customer") );
		source.push_back( manager->instanceNew("customerB6", "Customer") );
		source.push_back( manager->instanceNew("customerB7", "Customer") );
		source.push_back( manager->instanceNew("customerB8", "Customer") );
		source.push_back( manager->instanceNew("customerB9", "Customer") );
		source.push_back( manager->instanceNew("customerB10", "Customer") );
		loc.push_back( manager->instanceNew("ttB1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsB1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsB20", "Truck segment") );

		seg[20]->attributeIs("source", "customerB1");
		seg[21]->attributeIs("source", "ttB1");
		seg[21]->attributeIs("return segment", "tsB1");

		seg[22]->attributeIs("source", "customerB2");
		seg[23]->attributeIs("source", "ttB1");
		seg[23]->attributeIs("return segment", "tsB3");

		seg[24]->attributeIs("source", "customerB3");
		seg[25]->attributeIs("source", "ttB1");
		seg[25]->attributeIs("return segment", "tsB5");

		seg[26]->attributeIs("source", "customerB4");
		seg[27]->attributeIs("source", "ttB1");
		seg[27]->attributeIs("return segment", "tsB7");

		seg[28]->attributeIs("source", "customerB5");
		seg[29]->attributeIs("source", "ttB1");
		seg[29]->attributeIs("return segment", "tsB9");

		seg[30]->attributeIs("source", "customerB6");
		seg[31]->attributeIs("source", "ttB1");
		seg[31]->attributeIs("return segment", "tsB11");

		seg[32]->attributeIs("source", "customerB7");
		seg[33]->attributeIs("source", "ttB1");
		seg[33]->attributeIs("return segment", "tsB13");

		seg[34]->attributeIs("source", "customerB8");
		seg[35]->attributeIs("source", "ttB1");
		seg[35]->attributeIs("return segment", "tsB15");

		seg[36]->attributeIs("source", "customerB9");
		seg[37]->attributeIs("source", "ttB1");
		seg[37]->attributeIs("return segment", "tsB17");

		seg[38]->attributeIs("source", "customerB10");
		seg[39]->attributeIs("source", "ttB1");
		seg[39]->attributeIs("return segment", "tsB19");

		loc.push_back( manager->instanceNew("customerC1", "Customer") );
		source.push_back( manager->instanceNew("customerC2", "Customer") );
		source.push_back( manager->instanceNew("customerC3", "Customer") );
		source.push_back( manager->instanceNew("customerC4", "Customer") );
		source.push_back( manager->instanceNew("customerC5", "Customer") );
		source.push_back( manager->instanceNew("customerC6", "Customer") );
		source.push_back( manager->instanceNew("customerC7", "Customer") );
		source.push_back( manager->instanceNew("customerC8", "Customer") );
		source.push_back( manager->instanceNew("customerC9", "Customer") );
		source.push_back( manager->instanceNew("customerC10", "Customer") );
		loc.push_back( manager->instanceNew("ttC1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsC1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsC20", "Truck segment") );

		seg[40]->attributeIs("source", "customerC1");
		seg[41]->attributeIs("source", "ttC1");
		seg[41]->attributeIs("return segment", "tsC1");

		seg[42]->attributeIs("source", "customerC2");
		seg[43]->attributeIs("source", "ttC1");
		seg[43]->attributeIs("return segment", "tsC3");

		seg[44]->attributeIs("source", "customerC3");
		seg[45]->attributeIs("source", "ttC1");
		seg[45]->attributeIs("return segment", "tsC5");

		seg[46]->attributeIs("source", "customerC4");
		seg[47]->attributeIs("source", "ttC1");
		seg[47]->attributeIs("return segment", "tsC7");

		seg[48]->attributeIs("source", "customerC5");
		seg[49]->attributeIs("source", "ttC1");
		seg[49]->attributeIs("return segment", "tsC9");

		seg[50]->attributeIs("source", "customerC6");
		seg[51]->attributeIs("source", "ttC1");
		seg[51]->attributeIs("return segment", "tsC11");

		seg[52]->attributeIs("source", "customerC7");
		seg[53]->attributeIs("source", "ttC1");
		seg[53]->attributeIs("return segment", "tsC13");

		seg[54]->attributeIs("source", "customerC8");
		seg[55]->attributeIs("source", "ttC1");
		seg[55]->attributeIs("return segment", "tsC15");

		seg[56]->attributeIs("source", "customerC9");
		seg[57]->attributeIs("source", "ttC1");
		seg[57]->attributeIs("return segment", "tsC17");

		seg[58]->attributeIs("source", "customerC10");
		seg[59]->attributeIs("source", "ttC1");
		seg[59]->attributeIs("return segment", "tsC19");

		source.push_back( manager->instanceNew("customerD1", "Customer") );
		source.push_back( manager->instanceNew("customerD2", "Customer") );
		source.push_back( manager->instanceNew("customerD3", "Customer") );
		source.push_back( manager->instanceNew("customerD4", "Customer") );
		source.push_back( manager->instanceNew("customerD5", "Customer") );
		source.push_back( manager->instanceNew("customerD6", "Customer") );
		source.push_back( manager->instanceNew("customerD7", "Customer") );
		source.push_back( manager->instanceNew("customerD8", "Customer") );
		source.push_back( manager->instanceNew("customerD9", "Customer") );
		source.push_back( manager->instanceNew("customerD10", "Customer") );
		loc.push_back( manager->instanceNew("ttD1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsD1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsD20", "Truck segment") );

		seg[60]->attributeIs("source", "customerD1");
		seg[61]->attributeIs("source", "ttD1");
		seg[61]->attributeIs("return segment", "tsD1");

		seg[62]->attributeIs("source", "customerD2");
		seg[63]->attributeIs("source", "ttD1");
		seg[63]->attributeIs("return segment", "tsD3");

		seg[64]->attributeIs("source", "customerD3");
		seg[65]->attributeIs("source", "ttD1");
		seg[65]->attributeIs("return segment", "tsD5");

		seg[66]->attributeIs("source", "customerD4");
		seg[67]->attributeIs("source", "ttD1");
		seg[67]->attributeIs("return segment", "tsD7");

		seg[68]->attributeIs("source", "customerD5");
		seg[69]->attributeIs("source", "ttD1");
		seg[69]->attributeIs("return segment", "tsD9");

		seg[70]->attributeIs("source", "customerD6");
		seg[71]->attributeIs("source", "ttD1");
		seg[71]->attributeIs("return segment", "tsD11");

		seg[72]->attributeIs("source", "customerD7");
		seg[73]->attributeIs("source", "ttD1");
		seg[73]->attributeIs("return segment", "tsD13");

		seg[74]->attributeIs("source", "customerD8");
		seg[75]->attributeIs("source", "ttD1");
		seg[75]->attributeIs("return segment", "tsD15");

		seg[76]->attributeIs("source", "customerD9");
		seg[77]->attributeIs("source", "ttD1");
		seg[77]->attributeIs("return segment", "tsD17");

		seg[78]->attributeIs("source", "customerD10");
		seg[79]->attributeIs("source", "ttD1");
		seg[79]->attributeIs("return segment", "tsD19");

		source.push_back( manager->instanceNew("customerE1", "Customer") );
		source.push_back( manager->instanceNew("customerE2", "Customer") );
		source.push_back( manager->instanceNew("customerE3", "Customer") );
		source.push_back( manager->instanceNew("customerE4", "Customer") );
		source.push_back( manager->instanceNew("customerE5", "Customer") );
		source.push_back( manager->instanceNew("customerE6", "Customer") );
		source.push_back( manager->instanceNew("customerE7", "Customer") );
		source.push_back( manager->instanceNew("customerE8", "Customer") );
		source.push_back( manager->instanceNew("customerE9", "Customer") );
		source.push_back( manager->instanceNew("customerE10", "Customer") );
		loc.push_back( manager->instanceNew("ttE1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsE1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsE20", "Truck segment") );

		seg[80]->attributeIs("source", "customerE1");
		seg[81]->attributeIs("source", "ttE1");
		seg[81]->attributeIs("return segment", "tsE1");

		seg[82]->attributeIs("source", "customerE2");
		seg[83]->attributeIs("source", "ttE1");
		seg[83]->attributeIs("return segment", "tsE3");

		seg[84]->attributeIs("source", "customerE3");
		seg[85]->attributeIs("source", "ttE1");
		seg[85]->attributeIs("return segment", "tsE5");

		seg[86]->attributeIs("source", "customerE4");
		seg[87]->attributeIs("source", "ttE1");
		seg[87]->attributeIs("return segment", "tsE7");

		seg[88]->attributeIs("source", "customerE5");
		seg[89]->attributeIs("source", "ttE1");
		seg[89]->attributeIs("return segment", "tsE9");

		seg[90]->attributeIs("source", "customerE6");
		seg[91]->attributeIs("source", "ttE1");
		seg[91]->attributeIs("return segment", "tsE11");

		seg[92]->attributeIs("source", "customerE7");
		seg[93]->attributeIs("source", "ttE1");
		seg[93]->attributeIs("return segment", "tsE13");

		seg[94]->attributeIs("source", "customerE8");
		seg[95]->attributeIs("source", "ttE1");
		seg[95]->attributeIs("return segment", "tsE15");

		seg[96]->attributeIs("source", "customerE9");
		seg[97]->attributeIs("source", "ttE1");
		seg[97]->attributeIs("return segment", "tsE17");

		seg[98]->attributeIs("source", "customerE10");
		seg[99]->attributeIs("source", "ttE1");
		seg[99]->attributeIs("return segment", "tsE19");

		source.push_back( manager->instanceNew("customerF1", "Customer") );
		source.push_back( manager->instanceNew("customerF2", "Customer") );
		source.push_back( manager->instanceNew("customerF3", "Customer") );
		source.push_back( manager->instanceNew("customerF4", "Customer") );
		source.push_back( manager->instanceNew("customerF5", "Customer") );
		source.push_back( manager->instanceNew("customerF6", "Customer") );
		source.push_back( manager->instanceNew("customerF7", "Customer") );
		source.push_back( manager->instanceNew("customerF8", "Customer") );
		source.push_back( manager->instanceNew("customerF9", "Customer") );
		source.push_back( manager->instanceNew("customerF10", "Customer") );
		loc.push_back( manager->instanceNew("ttF1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsF1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsF20", "Truck segment") );

		seg[100]->attributeIs("source", "customerF1");
		seg[101]->attributeIs("source", "ttF1");
		seg[101]->attributeIs("return segment", "tsF1");

		seg[102]->attributeIs("source", "customerF2");
		seg[103]->attributeIs("source", "ttF1");
		seg[103]->attributeIs("return segment", "tsF3");

		seg[104]->attributeIs("source", "customerF3");
		seg[105]->attributeIs("source", "ttF1");
		seg[105]->attributeIs("return segment", "tsF5");

		seg[106]->attributeIs("source", "customerF4");
		seg[107]->attributeIs("source", "ttF1");
		seg[107]->attributeIs("return segment", "tsF7");

		seg[108]->attributeIs("source", "customerF5");
		seg[109]->attributeIs("source", "ttF1");
		seg[109]->attributeIs("return segment", "tsF9");

		seg[110]->attributeIs("source", "customerF6");
		seg[111]->attributeIs("source", "ttF1");
		seg[111]->attributeIs("return segment", "tsF11");

		seg[112]->attributeIs("source", "customerF7");
		seg[113]->attributeIs("source", "ttF1");
		seg[113]->attributeIs("return segment", "tsF13");

		seg[114]->attributeIs("source", "customerF8");
		seg[115]->attributeIs("source", "ttF1");
		seg[115]->attributeIs("return segment", "tsF15");

		seg[116]->attributeIs("source", "customerF9");
		seg[117]->attributeIs("source", "ttF1");
		seg[117]->attributeIs("return segment", "tsF17");

		seg[118]->attributeIs("source", "customerF10");
		seg[119]->attributeIs("source", "ttF1");
		seg[119]->attributeIs("return segment", "tsF19");

		source.push_back( manager->instanceNew("customerG1", "Customer") );
		source.push_back( manager->instanceNew("customerG2", "Customer") );
		source.push_back( manager->instanceNew("customerG3", "Customer") );
		source.push_back( manager->instanceNew("customerG4", "Customer") );
		source.push_back( manager->instanceNew("customerG5", "Customer") );
		source.push_back( manager->instanceNew("customerG6", "Customer") );
		source.push_back( manager->instanceNew("customerG7", "Customer") );
		source.push_back( manager->instanceNew("customerG8", "Customer") );
		source.push_back( manager->instanceNew("customerG9", "Customer") );
		source.push_back( manager->instanceNew("customerG10", "Customer") );
		loc.push_back( manager->instanceNew("ttG1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsG1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsG20", "Truck segment") );

		seg[120]->attributeIs("source", "customerG1");
		seg[121]->attributeIs("source", "ttG1");
		seg[121]->attributeIs("return segment", "tsG1");

		seg[122]->attributeIs("source", "customerG2");
		seg[123]->attributeIs("source", "ttG1");
		seg[123]->attributeIs("return segment", "tsG3");

		seg[124]->attributeIs("source", "customerG3");
		seg[125]->attributeIs("source", "ttG1");
		seg[125]->attributeIs("return segment", "tsG5");

		seg[126]->attributeIs("source", "customerG4");
		seg[127]->attributeIs("source", "ttG1");
		seg[127]->attributeIs("return segment", "tsG7");

		seg[128]->attributeIs("source", "customerG5");
		seg[129]->attributeIs("source", "ttG1");
		seg[129]->attributeIs("return segment", "tsG9");

		seg[130]->attributeIs("source", "customerG6");
		seg[131]->attributeIs("source", "ttG1");
		seg[131]->attributeIs("return segment", "tsG11");

		seg[132]->attributeIs("source", "customerG7");
		seg[133]->attributeIs("source", "ttG1");
		seg[133]->attributeIs("return segment", "tsG13");

		seg[134]->attributeIs("source", "customerG8");
		seg[135]->attributeIs("source", "ttG1");
		seg[135]->attributeIs("return segment", "tsG15");

		seg[136]->attributeIs("source", "customerG9");
		seg[137]->attributeIs("source", "ttG1");
		seg[137]->attributeIs("return segment", "tsG17");

		seg[138]->attributeIs("source", "customerG10");
		seg[139]->attributeIs("source", "ttG1");
		seg[139]->attributeIs("return segment", "tsG19");

		source.push_back( manager->instanceNew("customerH1", "Customer") );
		source.push_back( manager->instanceNew("customerH2", "Customer") );
		source.push_back( manager->instanceNew("customerH3", "Customer") );
		source.push_back( manager->instanceNew("customerH4", "Customer") );
		source.push_back( manager->instanceNew("customerH5", "Customer") );
		source.push_back( manager->instanceNew("customerH6", "Customer") );
		source.push_back( manager->instanceNew("customerH7", "Customer") );
		source.push_back( manager->instanceNew("customerH8", "Customer") );
		source.push_back( manager->instanceNew("customerH9", "Customer") );
		source.push_back( manager->instanceNew("customerH10", "Customer") );
		loc.push_back( manager->instanceNew("ttH1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsH1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsH20", "Truck segment") );

		seg[140]->attributeIs("source", "customerH1");
		seg[141]->attributeIs("source", "ttH1");
		seg[141]->attributeIs("return segment", "tsH1");

		seg[142]->attributeIs("source", "customerH2");
		seg[143]->attributeIs("source", "ttH1");
		seg[143]->attributeIs("return segment", "tsH3");

		seg[144]->attributeIs("source", "customerH3");
		seg[145]->attributeIs("source", "ttH1");
		seg[145]->attributeIs("return segment", "tsH5");

		seg[146]->attributeIs("source", "customerH4");
		seg[147]->attributeIs("source", "ttH1");
		seg[147]->attributeIs("return segment", "tsH7");

		seg[148]->attributeIs("source", "customerH5");
		seg[149]->attributeIs("source", "ttH1");
		seg[149]->attributeIs("return segment", "tsH9");

		seg[150]->attributeIs("source", "customerH6");
		seg[151]->attributeIs("source", "ttH1");
		seg[151]->attributeIs("return segment", "tsH11");

		seg[152]->attributeIs("source", "customerH7");
		seg[153]->attributeIs("source", "ttH1");
		seg[153]->attributeIs("return segment", "tsH13");

		seg[154]->attributeIs("source", "customerH8");
		seg[155]->attributeIs("source", "ttH1");
		seg[155]->attributeIs("return segment", "tsH15");

		seg[156]->attributeIs("source", "customerH9");
		seg[157]->attributeIs("source", "ttH1");
		seg[157]->attributeIs("return segment", "tsH17");

		seg[158]->attributeIs("source", "customerH10");
		seg[159]->attributeIs("source", "ttH1");
		seg[159]->attributeIs("return segment", "tsH19");

		source.push_back( manager->instanceNew("customerI1", "Customer") );
		source.push_back( manager->instanceNew("customerI2", "Customer") );
		source.push_back( manager->instanceNew("customerI3", "Customer") );
		source.push_back( manager->instanceNew("customerI4", "Customer") );
		source.push_back( manager->instanceNew("customerI5", "Customer") );
		source.push_back( manager->instanceNew("customerI6", "Customer") );
		source.push_back( manager->instanceNew("customerI7", "Customer") );
		source.push_back( manager->instanceNew("customerI8", "Customer") );
		source.push_back( manager->instanceNew("customerI9", "Customer") );
		source.push_back( manager->instanceNew("customerI10", "Customer") );
		loc.push_back( manager->instanceNew("ttI1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsI1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsI20", "Truck segment") );

		seg[160]->attributeIs("source", "customerI1");
		seg[161]->attributeIs("source", "ttI1");
		seg[161]->attributeIs("return segment", "tsI1");

		seg[162]->attributeIs("source", "customerI2");
		seg[163]->attributeIs("source", "ttI1");
		seg[163]->attributeIs("return segment", "tsI3");

		seg[164]->attributeIs("source", "customerI3");
		seg[165]->attributeIs("source", "ttI1");
		seg[165]->attributeIs("return segment", "tsI5");

		seg[166]->attributeIs("source", "customerI4");
		seg[167]->attributeIs("source", "ttI1");
		seg[167]->attributeIs("return segment", "tsI7");

		seg[168]->attributeIs("source", "customerI5");
		seg[169]->attributeIs("source", "ttI1");
		seg[169]->attributeIs("return segment", "tsI9");

		seg[170]->attributeIs("source", "customerI6");
		seg[171]->attributeIs("source", "ttI1");
		seg[171]->attributeIs("return segment", "tsI11");

		seg[172]->attributeIs("source", "customerI7");
		seg[173]->attributeIs("source", "ttI1");
		seg[173]->attributeIs("return segment", "tsI13");

		seg[174]->attributeIs("source", "customerI8");
		seg[175]->attributeIs("source", "ttI1");
		seg[175]->attributeIs("return segment", "tsI15");

		seg[176]->attributeIs("source", "customerI9");
		seg[177]->attributeIs("source", "ttI1");
		seg[177]->attributeIs("return segment", "tsI17");

		seg[178]->attributeIs("source", "customerI10");
		seg[179]->attributeIs("source", "ttI1");
		seg[179]->attributeIs("return segment", "tsI19");

		source.push_back( manager->instanceNew("customerJ1", "Customer") );
		source.push_back( manager->instanceNew("customerJ2", "Customer") );
		source.push_back( manager->instanceNew("customerJ3", "Customer") );
		source.push_back( manager->instanceNew("customerJ4", "Customer") );
		source.push_back( manager->instanceNew("customerJ5", "Customer") );
		source.push_back( manager->instanceNew("customerJ6", "Customer") );
		source.push_back( manager->instanceNew("customerJ7", "Customer") );
		source.push_back( manager->instanceNew("customerJ8", "Customer") );
		source.push_back( manager->instanceNew("customerJ9", "Customer") );
		source.push_back( manager->instanceNew("customerJ10", "Customer") );
		loc.push_back( manager->instanceNew("ttJ1", "Truck terminal") );
		
		seg.push_back( manager->instanceNew("tsJ1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsJ20", "Truck segment") );

		seg[180]->attributeIs("source", "customerJ1");
		seg[181]->attributeIs("source", "ttJ1");
		seg[181]->attributeIs("return segment", "tsJ1");

		seg[182]->attributeIs("source", "customerJ2");
		seg[183]->attributeIs("source", "ttJ1");
		seg[183]->attributeIs("return segment", "tsJ3");

		seg[184]->attributeIs("source", "customerJ3");
		seg[185]->attributeIs("source", "ttJ1");
		seg[185]->attributeIs("return segment", "tsJ5");

		seg[186]->attributeIs("source", "customerJ4");
		seg[187]->attributeIs("source", "ttJ1");
		seg[187]->attributeIs("return segment", "tsJ7");

		seg[188]->attributeIs("source", "customerJ5");
		seg[189]->attributeIs("source", "ttJ1");
		seg[189]->attributeIs("return segment", "tsJ9");

		seg[190]->attributeIs("source", "customerJ6");
		seg[191]->attributeIs("source", "ttJ1");
		seg[191]->attributeIs("return segment", "tsJ11");

		seg[192]->attributeIs("source", "customerJ7");
		seg[193]->attributeIs("source", "ttJ1");
		seg[193]->attributeIs("return segment", "tsJ13");

		seg[194]->attributeIs("source", "customerJ8");
		seg[195]->attributeIs("source", "ttJ1");
		seg[195]->attributeIs("return segment", "tsJ15");

		seg[196]->attributeIs("source", "customerJ9");
		seg[197]->attributeIs("source", "ttJ1");
		seg[197]->attributeIs("return segment", "tsJ17");

		seg[198]->attributeIs("source", "customerJ10");
		seg[199]->attributeIs("source", "ttJ1");
		seg[199]->attributeIs("return segment", "tsJ19");

		// 10 truck terminals connected to one, ttK1
		loc.push_back( manager->instanceNew("ttK1", "Truck terminal") );

		seg.push_back( manager->instanceNew("tsK1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK2", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK3", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK4", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK5", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK6", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK7", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK8", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK9", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK10", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK11", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK12", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK13", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK14", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK15", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK16", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK17", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK18", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK19", "Truck segment") );
		seg.push_back( manager->instanceNew("tsK20", "Truck segment") );

		seg[200]->attributeIs("source", "ttA1");
		seg[201]->attributeIs("source", "ttK1");
		seg[201]->attributeIs("return segment", "tsK1");

		seg[202]->attributeIs("source", "ttB1");
		seg[203]->attributeIs("source", "ttK1");
		seg[203]->attributeIs("return segment", "tsK3");

		seg[204]->attributeIs("source", "ttC1");
		seg[205]->attributeIs("source", "ttK1");
		seg[205]->attributeIs("return segment", "tsK5");

		seg[206]->attributeIs("source", "ttD1");
		seg[207]->attributeIs("source", "ttK1");
		seg[207]->attributeIs("return segment", "tsK7");

		seg[208]->attributeIs("source", "ttE1");
		seg[209]->attributeIs("source", "ttK1");
		seg[209]->attributeIs("return segment", "tsK9");

		seg[210]->attributeIs("source", "ttF1");
		seg[211]->attributeIs("source", "ttK1");
		seg[211]->attributeIs("return segment", "tsK11");

		seg[212]->attributeIs("source", "ttG1");
		seg[213]->attributeIs("source", "ttK1");
		seg[213]->attributeIs("return segment", "tsK13");

		seg[214]->attributeIs("source", "ttH1");
		seg[215]->attributeIs("source", "ttK1");
		seg[215]->attributeIs("return segment", "tsK15");

		seg[216]->attributeIs("source", "ttI1");
		seg[217]->attributeIs("source", "ttK1");
		seg[217]->attributeIs("return segment", "tsK17");

		seg[218]->attributeIs("source", "ttJ1");
		seg[219]->attributeIs("source", "ttK1");
		seg[219]->attributeIs("return segment", "tsK19");

		// Connect ttK1 to destination Customer
		loc.push_back( manager->instanceNew("CustomerL1", "Customer") );
		seg.push_back( manager->instanceNew("tsL1", "Truck segment") );
		seg.push_back( manager->instanceNew("tsL2", "Truck segment") );

		seg[220]->attributeIs("source", "ttK1");
		seg[221]->attributeIs("source", "CustomerL1");
		seg[221]->attributeIs("return segment", "tsL1");

	    Ptr<Instance> stats = manager->instanceNew("myStats", "Stats");

	    Ptr<Instance> fleet = manager->instanceNew("Fleet", "Fleet");
	    fleet->attributeIs("Truck speed", "60");
	    fleet->attributeIs("Truck capacity", "50");

		Ptr<Instance> conn = manager->instanceNew("myConn", "Conn");
		conn->attributeIs("routing algorithm", "Dijkstra"); 

        vector< Ptr<Instance> >::iterator i;
        for (i = source.begin(); i != source.end(); i++) {
            (*i)->attributeIs("Transfer Rate", "1");
            (*i)->attributeIs("Shipment Size", "1000");
            (*i)->attributeIs("Destination", "CustomerL1");
        }

		conn->attributeIs("simulation started", ""); 
	    Activity::Manager::Ptr activityManager = activityManagerInstance();
	    activityManager->nowIs(1000.0);

	    cout << "cost CustomerL1: " << stats->attribute("cost CustomerL1") << endl;
	    cout << "received CustomerL1: " << stats->attribute("received CustomerL1") << endl;
	    cout << "latency CustomerL1: " << stats->attribute("latency CustomerL1") << endl;

	    cout << "forwarded tsL1: " << stats->attribute("forwarded tsL1") << endl;
	    cout << "refused tsL1: "  << stats->attribute("refused tsL1") << endl;
	    cout << "fragmented tsL1: "  << stats->attribute("fragmented tsL1") << endl; 

  }
  catch(Exception e)
  {
	cout << e.what() << endl;
  }
  catch(...)
  {
  }
}

void hourGlass( vector< Ptr<Instance> >& loc, vector< Ptr<Instance> >& seg, Ptr<Instance::Manager> manager )
{
	// Locations
	loc.push_back( manager->instanceNew("customer1", "Customer") );
	loc.push_back( manager->instanceNew("customer2", "Customer") );
	loc.push_back( manager->instanceNew("customer3", "Customer") );
	loc.push_back( manager->instanceNew("customer4", "Customer") );
	loc.push_back( manager->instanceNew("customer5", "Customer") );
	loc.push_back( manager->instanceNew("customer6", "Customer") );
	loc.push_back( manager->instanceNew("customer7", "Customer") );
	loc.push_back( manager->instanceNew("customer8", "Customer") );
	loc.push_back( manager->instanceNew("customer9", "Customer") );
	loc.push_back( manager->instanceNew("customer10", "Customer") );
	loc.push_back( manager->instanceNew("customer11", "Customer") );
	loc.push_back( manager->instanceNew("customer12", "Customer") );
	loc.push_back( manager->instanceNew("port1", "Port") );

	// Segments
	seg.push_back( manager->instanceNew("ps1", "Plane segment") );
	seg.push_back( manager->instanceNew("ps2", "Plane segment") );
	seg.push_back( manager->instanceNew("ps3", "Plane segment") );
	seg.push_back( manager->instanceNew("ps4", "Plane segment") );
	seg.push_back( manager->instanceNew("ps5", "Plane segment") );
	seg.push_back( manager->instanceNew("ps6", "Plane segment") );
	seg.push_back( manager->instanceNew("ps7", "Plane segment") );
	seg.push_back( manager->instanceNew("ps8", "Plane segment") );
	seg.push_back( manager->instanceNew("bs1", "Boat segment") );
	seg.push_back( manager->instanceNew("bs2", "Boat segment") );
	seg.push_back( manager->instanceNew("bs3", "Boat segment") );
	seg.push_back( manager->instanceNew("bs4", "Boat segment") );
	seg.push_back( manager->instanceNew("bs5", "Boat segment") );
	seg.push_back( manager->instanceNew("bs6", "Boat segment") );
	seg.push_back( manager->instanceNew("bs7", "Boat segment") );
	seg.push_back( manager->instanceNew("bs8", "Boat segment") );
	seg.push_back( manager->instanceNew("ts1", "Truck segment") );
	seg.push_back( manager->instanceNew("ts2", "Truck segment") );
	seg.push_back( manager->instanceNew("ts3", "Truck segment") );
	seg.push_back( manager->instanceNew("ts4", "Truck segment") );
	seg.push_back( manager->instanceNew("ts5", "Truck segment") );
	seg.push_back( manager->instanceNew("ts6", "Truck segment") );
	seg.push_back( manager->instanceNew("ts7", "Truck segment") );
	seg.push_back( manager->instanceNew("ts8", "Truck segment") );

	seg[0]->attributeIs("source", "customer1");
	seg[1]->attributeIs("source", "port1");
	seg[1]->attributeIs("return segment", "ps1");

	seg[2]->attributeIs("source", "customer2");
	seg[3]->attributeIs("source", "port1");
	seg[3]->attributeIs("return segment", "ps3");

	seg[4]->attributeIs("source", "customer3");
	seg[5]->attributeIs("source", "port1");
	seg[5]->attributeIs("return segment", "ps5");

	seg[6]->attributeIs("source", "customer4");
	seg[7]->attributeIs("source", "port1");
	seg[7]->attributeIs("return segment", "ps7");

	seg[8]->attributeIs("source", "customer5");
	seg[9]->attributeIs("source", "port1");
	seg[9]->attributeIs("return segment", "bs1");

	seg[10]->attributeIs("source", "customer6");
	seg[11]->attributeIs("source", "port1");
	seg[11]->attributeIs("return segment", "bs3");

	seg[12]->attributeIs("source", "customer7");
	seg[13]->attributeIs("source", "port1");
	seg[13]->attributeIs("return segment", "bs5");

	seg[14]->attributeIs("source", "customer8");
	seg[15]->attributeIs("source", "port1");
	seg[15]->attributeIs("return segment", "bs7");

	seg[16]->attributeIs("source", "customer9");
	seg[17]->attributeIs("source", "port1");
	seg[17]->attributeIs("return segment", "ts1");

	seg[18]->attributeIs("source", "customer10");
	seg[19]->attributeIs("source", "port1");
	seg[19]->attributeIs("return segment", "ts3");

	seg[20]->attributeIs("source", "customer11");
	seg[21]->attributeIs("source", "port1");
	seg[21]->attributeIs("return segment", "ts5");

	seg[22]->attributeIs("source", "customer12");
	seg[23]->attributeIs("source", "port1");
	seg[23]->attributeIs("return segment", "ts7");

}

int main(int argc, char *argv[]) {
    funnel();
    getchar();
    return 0;
}

