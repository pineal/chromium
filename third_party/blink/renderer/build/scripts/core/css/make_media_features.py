#!/usr/bin/env python

# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), '../..'))

from blinkbuild.name_style_converter import NameStyleConverter
import media_feature_symbol
import json5_generator
import template_expander


class MakeMediaFeaturesWriter(json5_generator.Writer):
    default_metadata = {
        'namespace': '',
        'export': '',
    }
    filters = {
        'symbol': media_feature_symbol.getMediaFeatureSymbolWithSuffix(''),
        'to_function_name': lambda symbol: NameStyleConverter(symbol).to_function_name(),
    }

    def __init__(self, json5_file_path, output_dir):
        super(MakeMediaFeaturesWriter, self).__init__(json5_file_path, output_dir)

        self._outputs = {
            ('media_features.h'): self.generate_header,
        }
        self._template_context = {
            'entries': self.json5_file.name_dictionaries,
            'input_files': self._input_files,
            'header_guard': self.make_header_guard(self._relative_output_dir + 'media_festures.h')
        }

    @template_expander.use_jinja('core/css/templates/media_features.h.tmpl', filters=filters)
    def generate_header(self):
        return self._template_context

if __name__ == '__main__':
    json5_generator.Maker(MakeMediaFeaturesWriter).main()
