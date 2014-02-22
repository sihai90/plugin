#include "../gameengine.contract/contract.h"
#include "DemoGame.h"
#include <iostream>

#include <plugin/contract.h>

class DemoActivator : public IPluginActivator, public IPluginServiceListener
{
public:
	DemoActivator() {

	}

	virtual ~DemoActivator() {

	}

	virtual void Start(IPluginContext* context, IPluginBundle* plugin) {
		plugin->AddServiceListener(this);
		plugin->RegisterService(typeid(gameengine::IGame), &mService);
	}

	virtual void Stop(IPluginBundle* plugin) {
		std::cout << "DemoActivator is deactivated" << std::endl;
	}

	virtual void OnServiceChanged(IPluginServiceReference* reference, Status status) {
		if (status == STATUS_REGISTERED) {
			const type_info& type = reference->GetType();
			if (type == typeid(gameengine::IComponent)) {
				auto component = dynamic_cast<gameengine::IComponent*>(reference->GetService());
				mService.AddComponent(component);
			}
		}
		std::cout << "DemoActivator -> Service status changed for type: " << reference->GetType().name() << std::endl;
	}
	
private:
	DemoGame mService;
};

DEFINE_PLUGIN(DemoActivator, "1.0.0");
