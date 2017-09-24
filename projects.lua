BOOK_CODE_PATH = "E:/book-code"
THIRD_PARTY = "E:/book-code/3rdparty"
WORK_PATH = os.getcwd()
includeexternal (BOOK_CODE_PATH .. "/premake-vs-include.lua")




workspace(path.getname(os.realpath(".")))
    language "C++"
    location "build/%{_ACTION}/%{wks.name}"    
    if _ACTION == "vs2015" then
        toolset "v140_xp"
    elseif _ACTION == "vs2013" then
        toolset "v120_xp"
    end

    --include (BOOK_CODE_PATH .. "/common.lua")    
    

    create_dll_project("clipboard-core", "src")
        defines { "BUILDING_DLL" }

    create_wtl_project("clipboard-ui", "src")
        links
        {
            "clipboard-core"
        }

--    group "examples"
--        matches = os.matchdirs("src/*")
--        for i = #matches, 1, -1 do
--            --p.w(path.getname(matches[i]))  
--            local project_name = path.getname(matches[i])
--            
--            create_wtl_project(project_name, "src")
--            
--            
--        end

    

        