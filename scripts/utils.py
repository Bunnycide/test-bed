import subprocess
import argparse
import os
import time
import re

MAKE_CLASS = "make-class"

HEADER_CONTENT = '''#ifndef {class_name}_H_
#define  {class_name}_H_

class {class_name} {{
    {class_name} ();
}};

#endif'''

SOURCE_CONTENT = '''#include <{class_name}.h>
'''

def create_file_relative(relative_path, content):
    # Get the absolute path by joining the current working directory with the relative path
    file_path = os.path.abspath(os.path.join(os.getcwd(), relative_path))
    
    # Create the directory structure if it doesn't exist
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    
    # Create the file and write content to it
    with open(file_path, 'w') as file:
        file.write(content)
    
    print(f"File created: {file_path}")

def make_class(**kwargs):
    
    create_file_relative("./inc/{0}.h".format(kwargs["name"]), HEADER_CONTENT.format(class_name=kwargs["name"]))
    create_file_relative("./src/{0}.cpp".format(kwargs["name"]), SOURCE_CONTENT.format(class_name=kwargs["name"]))

commands = {
    MAKE_CLASS : make_class
}

def define_cmd_args():
    # Initialize the main parser
    parser = argparse.ArgumentParser(description='Process some arguments.')

     # Create subparsers for different commands
    subparsers = parser.add_subparsers(dest='command', help='Sub-command help')

    # For making class files
    parser_make_class = subparsers.add_parser('make-class', help='Create a class')
    parser_make_class.add_argument('-name', type=str, required=True, help='Name of the class')
    
    return parser


def main():
    parser = define_cmd_args() 
    args = parser.parse_args()    
    
    commands[args.command](**vars(args))

if __name__ == "__main__":
    main()
