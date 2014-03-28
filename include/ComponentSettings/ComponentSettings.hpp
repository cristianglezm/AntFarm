#ifndef COMPONENT_SETTINGS_H
#define COMPONENT_SETTINGS_H
#include <string>
namespace ant{
    class ComponentSettings{
        private:

        public:
            ComponentSettings();
            void loadSettings(const std::string& filename);
            ~ComponentSettings();
    };
};
#endif // COMPONENT_SETTINGS_H
