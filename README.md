[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5c6276ac764b48e88ba7beeaf180a32c)](https://www.codacy.com/app/tolstenko/mobagen?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=InfiniBrains/mobagen&amp;utm_campaign=Badge_Grade)[![Build status](https://tolstenko.visualstudio.com/mobagen/_apis/build/status/mobagen-CI)](https://tolstenko.visualstudio.com/mobagen/_build/latest?definitionId=4) [![Active Contributors](https://api.gitential.com/accounts/758/projects/809/badges/active-contributors.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Code Volume](https://api.gitential.com/accounts/758/projects/809/badges/code-volume.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Coding Hours](https://api.gitential.com/accounts/758/projects/809/badges/coding-hours.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Efficiency](https://api.gitential.com/accounts/758/projects/809/badges/efficiency.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Utilization](https://api.gitential.com/accounts/758/projects/809/badges/utilization.svg)](https://gitential.com/accounts/758/projects/809/share?uuid=7533eb0d-42e1-41f1-8f8f-a8f8f1fdce70&utm_source=shield&utm_medium=shield&utm_campaign=809) [![Coverity](https://scan.coverity.com/projects/14798/badge.svg)](https://scan.coverity.com/projects/infinibrains-mobagen)  [![Coverage Status](https://coveralls.io/repos/github/InfiniBrains/mobagen/badge.svg?branch=master)](https://coveralls.io/github/InfiniBrains/mobagen?branch=master)

![](./assets/logo.png)

Welcome to the **MoBaGEn**. The **MO**dule **BA**sed **G**ame **EN**gine. 

**MoBaGEn** is a free lightweight, cross-platform 3D Game Engine implemented in C++. It will support scripts in C#(Mono), Javascript(V8), python and Lua.

## Feature:
- Scene Graph
- 3D model loading (most common file formats)
- Entity/Component Object Model (WiP - Migrating to use something similar to Unity3D)
- Lighting system (ambient/spot/point/directional lights) - Forward rendering
- Bump mapping
- Perspective/Ortho camera
- Object picking (basic ray tracing/sphere collider collision detection) (WiP - We plan to integrate bullet physics to do it)
- Fully cross platform - Windows (Tested: Visual Studio, MinGW; Continous integrated: MinGW on linux), HTML5 (via Emscripten), Linux (gcc and clang), Android (NDK, not integrated to CI yet), iOS(WiP - [Planned](https://github.com/InfiniBrains/mobagen/issues/39)), OSX(Xcode and terminal tools).

## License
Licensed under the [![WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-4.png)](http://www.wtfpl.net/). In short: you can do whatever you want to do, and we kindly ask you for a contribution to pay our bills. See [LICENSE](LICENSE.md) for details.

## Contributing

[Join us](https://infinibrains-inviter.herokuapp.com/) on Slack [![Slack Status](https://infinibrains-inviter.herokuapp.com/badge.svg)](https://infinibrains-inviter.herokuapp.com)!

[Chat with us!](https://chat.whatsapp.com/HdkvAXNLoWk7uRuV1A4E8F) on WhatsApp <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/19/WhatsApp_logo-color-vertical.svg/1024px-WhatsApp_logo-color-vertical.svg.png" data-canonical-src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/19/WhatsApp_logo-color-vertical.svg/1024px-WhatsApp_logo-color-vertical.svg.png" width="20" height="20" />
 
Before making pull requests, please read the [Contribution checklist](CONTRIBUTION.md) and [Coding Conventions](CODINGCONVENTION.md) pages from the documentation.

## Branches
We publish source for the engine in three rolling branches:

The **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)** tracks [release changes](https://github.com/InfiniBrains/mobagen/commits/master) by our engine team. It is extensively tested by our QA team and makes a great starting point for learning the engine or making your own games. We work hard to make releases stable and reliable, and aim to publish new releases every few months.

The **[development branch](https://github.com/InfiniBrains/mobagen/tree/development)** This is the cutting edge and may be buggy - it may not even compile. Battle-hardened developers eager to work lock-step with us on the latest and greatest should head here.

The **_feature_ branch** where _feature_ is the name of a given feature being developed. When it is done, it will merge its differences into the **[master branch](https://github.com/InfiniBrains/mobagen/tree/master)**.

Other short-lived branches may pop-up from time to time as we stabilize new releases or hotfixes.

## Documentation
The documentation is also available online at [Documentation](docs/HEAD/index.html) (Work in Progress. Help Needed.)

Documentation on how to build MoBaGEn: [Building](BUILDING.md)

## Samples
[Midas Miner](https://infinibrains.github.io/mobagen/midasminer.html):
![Midas Miner](https://i.imgur.com/t1Vp8RV.jpg)

## History
The change history is available online at [History](docs/HEAD/history.html) (Work in Progress. Help Needed.)

## Third Parties
This project was made using these open-sourced [third parties](THIRDPARTIES.md).

## Contributors
MoBaGEn development is made by these awesome [People](PEOPLE.md), and the top contributors are:
- [Alexandre Tolstenko](http://linkedin.com/in/aletolstenko/)
- [Marcos Soares](http://linkedin.com/in/marcos-soares-391718141/)
- [Mauro Gavioli](https://www.linkedin.com/in/mauro-gavioli-de-carvalho-245691163/)

## Sponsorship
This project is sponsored via [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=tolstenko@gmail.com) and [Patreon](https://www.patreon.com/infinibrains) by these kind people:
- [Alexandre Tolstenko](http://linkedin.com/in/aletolstenko/)

## Finance Report
In order to report our costs properly via [OpenCollective](https://opencollective.com/) we need to achieve at least 100 stars in this repository. So please star us!

## Development Log
You can see our reports and tutorials via our channel in [YouTube](https://www.youtube.com/tolstenko) or our [Blog](http://infinibrains.com/blog)

<div align="center">
  <a href="https://www.youtube.com/watch?v=oY6Epmaxixk"><img src="https://img.youtube.com/vi/oY6Epmaxixk/0.jpg" alt="MoBaGEn Intro"></a>
</div>

