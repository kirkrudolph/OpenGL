#include "Test.hpp"
#include "imgui-1.88/imgui.h"

namespace test
{
    

    TestMenu::TestMenu(Test*& currentTestPointer)
        : m_CurrentTest(currentTestPointer)
    {
    }
    
    void TestMenu::OnImguiRender()
    {
        for (auto& test : m_Tests)
        {
            if(ImGui::Button(test.first.c_str()))
                m_CurrentTest = test.second();
        }
        
    }
} // namespace test
