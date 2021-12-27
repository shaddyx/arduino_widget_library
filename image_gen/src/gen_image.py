import dataclasses
import logging
import typing

import jinja2

logging.basicConfig(level=logging.INFO)

from PIL import Image

import argparse

parser = argparse.ArgumentParser(description='Image converter')
parser.add_argument('file', type=str)
parser.add_argument('outputFile', type=str)

args = parser.parse_args()


@dataclasses.dataclass
class Img:
    name: str
    w: int
    h: int
    size: int
    data: typing.List[int]

def open_image(f: str):
    with Image.open(f) as im:
        im_gs = list(im.getdata())
        im_gs = map(lambda x: x[0] > 0 or x[1] > 0 or x[2] > 0 or x[3] > 0, im_gs)
        im_gs = list(map(lambda x: 0 if x else 1, im_gs))
        data = []
        for k in range(len(im_gs)):
            if im_gs[k]:
                chunk = 1
            else:
                chunk = 0
            if not k % 8:
                data.append(chunk)
            else:
                data[-1] = data[-1] | (chunk << (k % 8))
        logging.info("data size is: {}".format(len(data)))
        return Img(
            f.split("/")[-1].split(".")[0],
            im.width,
            im.height,
            len(data),
            data
        )

def generate(img: Img):
    templateLoader = jinja2.FileSystemLoader(searchpath="./templates")
    templateEnv = jinja2.Environment(loader=templateLoader, trim_blocks=True, lstrip_blocks=True, line_comment_prefix='//*')
    TEMPLATE_FILE = "image.h"
    template = templateEnv.get_template(TEMPLATE_FILE)
    outputText = template.render({
        "img":img
    })
    return outputText

output_image = open_image(args.file)
print(output_image)
open(args.outputFile, "w").write(generate(output_image))
