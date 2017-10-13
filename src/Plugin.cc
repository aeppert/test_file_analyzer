#include "plugin/Plugin.h"

#include "TEST.h"

namespace file_analysis { class TEST; }

namespace plugin {
	namespace BRO_TEST {
		class Plugin : public plugin::Plugin
		{
			public:
				plugin::Configuration Configure()
				{
					AddComponent(new ::file_analysis::Component("TEST", ::file_analysis::TEST::Instantiate));

					plugin::Configuration config;
					config.name = "BRO::TEST";
					config.description = "TEST File Analyzer";
					config.version.major = 1;
					config.version.minor = 0;
					
					return config;
				}
		} plugin;
	}
}
