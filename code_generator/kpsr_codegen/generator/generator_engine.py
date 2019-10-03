# Klepsydra Core Modules
# Copyright (C) 2019-2020  Klepsydra Technologies GmbH
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# -*- coding: utf-8 -*-

## @package generator
# \defgroup kpsr-code-generator
# generator package

import errno
import os
import sys
from os import walk

import yaml
from jinja2 import Environment, FileSystemLoader

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../kidl_data')))
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../preprocessor')))
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../processor')))

from configuration import Configuration

from preprocessor import Preprocessor

from poco_processor import PocoProcessor
from poco_processor import convert_to_lower_case_underscores
from poco_processor import split_namespace_class

from middleware_type import MiddlewareType

from ros_mapper_processor import RosMapperProcessor
from ros_msg_processor import RosMsgProcessor

from dds_mapper_processor import DdsMapperProcessor
from dds_idl_processor import DdsIdlProcessor

from zmq_serializer_processor import ZmqSerializerProcessor

from node_handler_processor import NodeHandlerProcessor

## Doc for the write_contents_to_file function
# \ingroup kpsr-code-generator
#
# More details
def write_contents_to_file(poco_file_name, poco_template_content):
    if not os.path.exists(os.path.dirname(poco_file_name)):
        try:
            os.makedirs(os.path.dirname(poco_file_name))
        except OSError as exc:  # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise
    poco_file = open(poco_file_name, "w")
    poco_file.write(poco_template_content)
    poco_file.close()


## Doc for the Generator class
# \ingroup kpsr-code-generator
#
# More dtails
class Generator:
    ## The constructor
    # @param conf_path The configuration path (I suppose)
    # @param template_path The template path (I think)
    def __init__(self, conf_path, template_path):
        configuration = Configuration(conf_path)
        self.preprocessor = Preprocessor(configuration)
        self.poco_processor = PocoProcessor(configuration)

        self.ros_mapper_processor = RosMapperProcessor(configuration)
        self.ros_msg_processor = RosMsgProcessor(configuration)

        self.dds_mapper_processor = DdsMapperProcessor(configuration)
        self.dds_idl_processor = DdsIdlProcessor(configuration)

        self.zmq_serializer_processor = ZmqSerializerProcessor(configuration)

        self.node_handler_processor = NodeHandlerProcessor(configuration)

        env = Environment(
            loader=FileSystemLoader(template_path)
        )
        self.poco_template = env.get_template('poco_template.h')
        self.ros_mapper_template = env.get_template('ros_mapper_template.h')
        self.ros_msg_template = env.get_template('ros_template.msg')
        self.dds_mapper_template = env.get_template('dds_mapper_template.h')
        self.dds_idl_template = env.get_template('dds_template.idl')
        self.zmq_serializer_template = env.get_template('zmq_serializer_template.h')
        self.node_handler_template = env.get_template('node_handler_template.js')

    ## The render function
    # @param input_dir The input directory (I suppose)
    # @param output_dir The output directory (I suppose)
    # @param include_path
    # @param disable_ros
    # @param disable_dds
    # @param disable_zmq
    def render(self, input_dir, output_dir, include_path, disable_ros, disable_dds, disable_zmq):
        kidl_files = []
        for (dirpath, dirnames, filenames) in walk(input_dir):
            kidl_files.extend(filenames)
            break

        class_definitions = [self.read_kidl_file(input_dir, kidl_file, disable_zmq) for kidl_file in kidl_files]
        class_definition_dict = {class_definition.class_name: class_definition for class_definition in class_definitions}

        [self.generate_code(class_definition_dict, include_path, input_dir, kidl_file,
                            output_dir, disable_ros, disable_dds, disable_zmq) for kidl_file in kidl_files]

    def generate_code(self, class_definition_dict, include_path, input_dir, main_kidl_file, output_dir,
                      disable_ros, disable_dds, disable_zmq):
        main_class_definition = self.read_kidl_file(input_dir, main_kidl_file, disable_zmq)
        poco_definition = self.poco_processor.process(main_class_definition.class_name, class_definition_dict,
                                                      include_path)

        if not main_class_definition.already_exists:
            class_name = split_namespace_class(main_class_definition.class_name)[-1]
            poco_file_name = output_dir + "/poco/include/" + include_path + "/" + \
                             convert_to_lower_case_underscores(class_name) + ".h"
            poco_template_content = self.poco_template.render(definition=poco_definition)
            write_contents_to_file(poco_file_name, poco_template_content)

        ros_middleware_definition = main_class_definition.middlewares.get(MiddlewareType.ROS)
        if (not disable_ros) and ros_middleware_definition is not None:
            if not ros_middleware_definition.mapper_include_file:
                ros_mapper_definition = self.ros_mapper_processor.process(main_class_definition.class_name,
                                                                          class_definition_dict, include_path)
                ros_mapper_file_name = output_dir + "/rosstg/include/" + ros_middleware_definition.project_name + "/" \
                                       + convert_to_lower_case_underscores(class_name) + "_ros_mapper.h"
                ros_mapper_template_content = self.ros_mapper_template.render(definition=ros_mapper_definition)
                write_contents_to_file(ros_mapper_file_name, ros_mapper_template_content)

            if not ros_middleware_definition.already_exists:
                ros_msg_definition = self.ros_msg_processor.process(main_class_definition.class_name,
                                                                    class_definition_dict)
                ros_msg_file_name = output_dir + "/rosstg/msg/" + ros_middleware_definition.class_name + ".msg"
                ros_msg_template_content = self.ros_msg_template.render(definition=ros_msg_definition)
                write_contents_to_file(ros_msg_file_name, ros_msg_template_content)

            node_handler_definition = self.node_handler_processor.process(main_class_definition.class_name,
                                                                    class_definition_dict)
            node_handler_file_name = convert_to_lower_case_underscores(
                node_handler_definition.handler_name)+".js"
            node_handler_file_path = output_dir + "/rosstg/node/" + node_handler_file_name
            node_handler_template_content = self.node_handler_template.render(definition=node_handler_definition)
            write_contents_to_file(node_handler_file_path, node_handler_template_content)

        if (not disable_dds) and (main_class_definition.middlewares.get(MiddlewareType.DDS) is not None):
            if not main_class_definition.middlewares.get(MiddlewareType.DDS).mapper_include_file:
                dds_mapper_definition = self.dds_mapper_processor.process(main_class_definition.class_name,
                                                                          class_definition_dict, include_path)
                dds_mapper_file_name = output_dir + "/dds/include/" + include_path + "/dds/" \
                                       + convert_to_lower_case_underscores(class_name) + "_dds_mapper.h"
                dds_mapper_template_content = self.dds_mapper_template.render(definition=dds_mapper_definition)
                write_contents_to_file(dds_mapper_file_name, dds_mapper_template_content)

            if not main_class_definition.middlewares.get(MiddlewareType.DDS).already_exists:
                dds_idl_definition = self.dds_idl_processor.process(main_class_definition.class_name,
                                                                    class_definition_dict)
                dds_idl_file_name = output_dir + "/dds/idl/" + \
                                    convert_to_lower_case_underscores(dds_idl_definition.class_name) + ".idl"
                dds_idl_template_content = self.dds_idl_template.render(definition=dds_idl_definition)
                write_contents_to_file(dds_idl_file_name, dds_idl_template_content)

        if (not disable_zmq) and main_class_definition.middlewares.get(MiddlewareType.ZMQ) is not None:
            if not main_class_definition.middlewares.get(MiddlewareType.ZMQ).serializer_include_file:
                class_name = split_namespace_class(main_class_definition.class_name)[-1]
                zmq_serializer_definition = self.zmq_serializer_processor.process(main_class_definition.class_name,
                                                                                  class_definition_dict, include_path)
                zmq_serializer_file_name = output_dir + "/serialization/include/" + include_path + "/cereal/" \
                                       + convert_to_lower_case_underscores(class_name) + "_serializer.h"
                zmq_serializer_template_content = self.zmq_serializer_template.render(definition=zmq_serializer_definition)
                write_contents_to_file(zmq_serializer_file_name, zmq_serializer_template_content)

    def read_kidl_file(self, input_dir, kidl_file, disable_zmq):
        with open("%s%s" % (input_dir, kidl_file), 'r') as stream:
            try:
                class_definition_data = yaml.load(stream, Loader=yaml.FullLoader)
                class_definition = self.preprocessor.process(class_definition_data, disable_zmq)
                return class_definition
            except yaml.YAMLError as exc:
                print(exc)
                return None
