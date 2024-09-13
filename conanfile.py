import os
from conan import ConanFile
from conan.tools.files import copy
from conan.tools.cmake import cmake_layout, CMake
from conan.tools.build import check_min_cppstd


class trmRecipe(ConanFile):
    name = "trm"
    version = "0.1.0"
    # package_type = "library"

    # Optional metadata
    license = "BSD 3-Clause License"
    author = "Simone Palacino <simo.palacino@gmail.com>"
    url = "https://github.com/simopalacino/trm"
    description = "A Shared way to sync access of objects library for C++"
    topics = ("mutex", "reference", "shared", "sync", "arc", "mutex", "thread-safe")
    exports_sources = "include/*", "test/*"
    no_copy_source = True
    generators = "CMakeToolchain", "CMakeDeps"

    # Binary configuration
    settings = "os", "arch", "compiler", "build_type"

    # # Sources are located in the same place as this recipe, copy them to the recipe

    def validate(self):
        check_min_cppstd(self, 11)

    def requirements(self):
        self.test_requires("gtest/1.11.0")

    def layout(self):
        cmake_layout(self)
    
    # def generate(self):
    #     deps = CMakeDeps(self)
    #     deps.generate()
    #     tc = CMakeToolchain(self)
    #     tc.generate()

    # def build(self):
        # if not self.conf.get("tools.build:skip_test", default=False):
        #     cmake = CMake(self)
        #     cmake.configure(build_script_folder="test")
        #     cmake.build()
        #     self.run(os.path.join(self.cpp.build.bindir, "trm_tests"))
            

    def package(self):
        # copy(self, "*.hpp", src=self.source_folder, dst=self.package_folder)
        # cmake = CMake(self)
        # cmake.install()
        copy(self, pattern="*.h", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include"))
        copy(self, pattern="*.hpp", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include"))
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        # For header-only packages, libdirs and bindirs are not used
        # so it's necessary to set those as empty.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

    def package_id(self):
        self.info.clear()
